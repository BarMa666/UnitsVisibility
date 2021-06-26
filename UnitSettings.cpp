#include "UnitSettings.h"
#include "UnitManager.h"
#include "UnitVisibilityTester.h"
#include <locale>
#include <map>

#ifndef _TEST
static const UnitSettings::InputFileNameT SETTINGS_FILE_NAME_IN = _T("input.txt");
#else
static const UnitSettings::InputFileNameT SETTINGS_FILE_NAME_IN = _T("test_input.txt");
#endif

#ifndef _TEST
static const UnitSettings::InputFileNameT SETTINGS_FILE_NAME_OUT = _T("output.txt");
#else
static const UnitSettings::InputFileNameT SETTINGS_FILE_NAME_OUT = _T("test_output.txt");
#endif

enum class UNIT_SETTING_VALUE {Sector, Distance};

static const std::map<UNIT_SETTING_VALUE, UnitSettings::SettingsNameT> m_valueMap =
{
    {UNIT_SETTING_VALUE::Sector, _T("Sector")},
    {UNIT_SETTING_VALUE::Distance, _T("Distance")}
};

UnitSettings& UnitSettings::instance()
{
    static UnitSettings settings;
    return settings;
}

UnitSettings::UnitSettings()
    : m_unitDegreesVisibility(0)
    , m_unitDistanceVisibility(0)
    , out()
{
}

void UnitSettings::loadSettings()
{
    load(SETTINGS_FILE_NAME_IN);
}

void UnitSettings::saveResult()
{
    save(SETTINGS_FILE_NAME_OUT);
}

UnitSettings::DegreesT UnitSettings::getDegreesVisibility() const
{
    return m_unitDegreesVisibility;
}

UnitSettings::DistanceT UnitSettings::getDistanceVisibility() const
{
    return m_unitDistanceVisibility;
}

UnitSettings::DataHolderT& UnitSettings::operator<<(const UnitSettings::DataT& _data)
{
    out << _data;
    return out;
}

void UnitSettings::load(const InputFileNameT& _filename)
{
    try
    {
        SettingT line;
        tifstream fin(_filename);
        if (fin.is_open())
        {
            while (std::getline(fin, line))
            {
                if (!line.empty())
                {
                    setupSetting(line);
                }
            }
            fin.close();
        }
    }
    catch (...)
    {
        tcout << _T("load exception!");
    }
}

void UnitSettings::save(const OutputFileNameT& _filename)
{
    try
    {
        tofstream fout(_filename);
        if (fout.is_open())
        {
            fout.imbue(std::locale("ru_RU.UTF-8"));
            fout << out.str();
            fout.close();
        }
    }
    catch (...)
    {
        tcout << _T("save exception!");
    }
}

void UnitSettings::setupSetting(const SettingT& _setting)
{
    auto first = _setting.substr(0, _setting.find(_T(":")));
    if (first.find(m_valueMap.at(UNIT_SETTING_VALUE::Sector)) != tstring::npos)
    {
        m_unitDegreesVisibility = setupDegreesVisibility(_setting);
    }
    else if (first.find(m_valueMap.at(UNIT_SETTING_VALUE::Distance)) != tstring::npos)
    {
        m_unitDistanceVisibility = setupDistanceVisibility(_setting);
    }
    else
    {
        createUnit(_setting);
    }
}

UnitSettings::DegreesT UnitSettings::setupDegreesVisibility(const SettingT& _setting)
{
    tstringstream ss;
    ss << _setting.substr(_setting.find(_T(":")) + 1);
    UnitSettings::DegreesT res;
    ss >> res;
    return res;
}

UnitSettings::DistanceT UnitSettings::setupDistanceVisibility(const SettingT& _setting)
{
    return static_cast<unsigned>(std::stoul(_setting.substr(_setting.find(_T(":")) + 1)));
}

NameT UnitSettings::setupName(const SettingT& _setting)
{
    return _setting.substr(0, _setting.find(_T(":")));
}

PositionT UnitSettings::setupPosition(const SettingT& _setting)
{
    const auto& start_x = _setting.find(_T("(")) + 1;
    const auto& size_x = _setting.find(_T(","));
    const auto& x = _setting.substr(start_x, size_x - start_x);
    const auto& start_y = _setting.find(_T(",")) + 1;
    const auto& size_y = _setting.find(_T(")"));
    const auto& y = _setting.substr(start_y, size_y - start_y);
    return PositionT({ std::stof(x), std::stof(y) });
}

DirectionT UnitSettings::setupDirection(const SettingT& _setting)
{
    tstringstream ss;
    const auto& start_x = _setting.rfind(_T("(")) + 1;
    const auto& size_x = _setting.rfind(_T(","));
    ss << _setting.substr(start_x, size_x - start_x);
    Vector2::CoordT x = 0;
    ss >> x;
    ss.clear();
    const auto& start_y = _setting.rfind(_T(",")) + 1;
    const auto& size_y = _setting.rfind(_T(")"));
    ss << _setting.substr(start_y, size_y - start_y);
    Vector2::CoordT y = 0;
    ss >> y;
    return DirectionT({ x, y });
}

void UnitSettings::createUnit(const SettingT& _setting)
{
    const auto& name = setupName(_setting);
    const auto& position = setupPosition(_setting);
    const auto& direction = setupDirection(_setting);
#ifdef _TEST
    setupTestResult(_setting);
#endif
    UnitManager::instance().createUnit(name, position, direction);
}

#ifdef _TEST
void UnitSettings::setupTestResult(const SettingT& _setting)
{
    const auto& name = setupName(_setting);
    const auto& result_data = _setting.substr(_setting.find(_T("?")) + 1);
    UnitVisibilityTester::instance().addResult(name, result_data);
}
#endif
