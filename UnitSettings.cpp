#include "UnitSettings.h"
#include "UnitManager.h"
#include <map>

static const std::wstring SETTINGS_FILE_NAME = _T("input.txt");

enum class UNIT_SETTING_VALUE {Sector, Distance, Unit};

static const std::map<std::wstring, UNIT_SETTING_VALUE> m_valueMap =
{
    {_T("Sector"), UNIT_SETTING_VALUE::Sector},
    {_T("Distance"), UNIT_SETTING_VALUE::Distance},
    {_T("Unit"), UNIT_SETTING_VALUE::Unit}
};

UnitSettings::DegreesT UnitSettings::getDegreesVisibility() const
{
    return m_unitDegreesVisibility;
}

UnitSettings::DistanceT UnitSettings::getDistanceVisibility() const
{
    return m_unitDistanceVisibility;
}

UnitSettings::UnitSettings()
    : m_unitDegreesVisibility(0)
    , m_unitDistanceVisibility(0)
{
}

void UnitSettings::setupSetting(const SettingT& _setting)
{
    auto first = _setting.substr(0, _setting.find(_T(":")));
    if (first.find(_T("Unit")) != std::wstring::npos)
    {
        first = _T("Unit");
    }
    switch (m_valueMap.at(first))
    {
    case UNIT_SETTING_VALUE::Sector:
        m_unitDegreesVisibility = setupDegreesVisibility(_setting);
        break;
    case UNIT_SETTING_VALUE::Distance:
        m_unitDistanceVisibility = setupDistanceVisibility(_setting);
        break;
    case UNIT_SETTING_VALUE::Unit:
        createUnit(_setting);
        break;
    default:
        break;
    }
}

UnitSettings::DegreesT UnitSettings::setupDegreesVisibility(const SettingT& _setting)
{
    return std::stof(_setting.substr(_setting.find(_T(":")) + 1));
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
    const auto& start_x = _setting.rfind(_T("(")) + 1;
    const auto& size_x = _setting.rfind(_T(","));
    const auto& x = _setting.substr(start_x, size_x - start_x);
    const auto& start_y = _setting.rfind(_T(",")) + 1;
    const auto& size_y = _setting.rfind(_T(")"));
    const auto& y = _setting.substr(start_y, size_y - start_y);
    return DirectionT({ std::stof(x), std::stof(y) });
}

void UnitSettings::createUnit(const SettingT& _setting)
{
    const auto& name = setupName(_setting);
    const auto& position = setupPosition(_setting);
    const auto& direction = setupDirection(_setting);
    UnitManager::instance().createUnit(name, position, direction);
}

UnitSettings& UnitSettings::instance()
{
    static UnitSettings settings;
    return settings;
}

void UnitSettings::loadSettings()
{
    try
    {
        std::wstring line;
        std::wifstream fin(SETTINGS_FILE_NAME);
        if (fin.is_open())
        {
            while (std::getline(fin, line))
            {
                setupSetting(line);
            }
            fin.close();
        }
    }
    catch (...)
    {
        std::wcout << _T("loadSettings exception!");
    }
}
