#pragma once
#include "Types.h"

class Unit;

class UnitSettings
{
public:
	using DegreesT = float;
	using DistanceT = int;
	using InputFileNameT = tstring;
	using OutputFileNameT = tstring;
	using SettingsNameT = tstring;
	using DataT = tstring;
	using DataHolderT = tstringstream;
	using SettingT = tstring;

	static UnitSettings& instance();

	void loadSettings();
	void saveResult();

	UnitSettings(const UnitSettings&) = delete;
	UnitSettings& operator=(const UnitSettings&) = delete;
	UnitSettings(UnitSettings&&) = delete;
	UnitSettings& operator=(UnitSettings&&) = delete;

	DegreesT getDegreesVisibility() const;
	DistanceT getDistanceVisibility() const;

	DataHolderT& operator<<(const DataT& _data);

private:
	UnitSettings();

	void load(const InputFileNameT&);
	void save(const OutputFileNameT&);
	void setupSetting(const SettingT&);
	DegreesT setupDegreesVisibility(const SettingT&);
	DistanceT setupDistanceVisibility(const SettingT&);

	NameT setupName(const SettingT&);
	PositionT setupPosition(const SettingT&);
	DirectionT setupDirection(const SettingT&);
#ifdef _TEST
	void setupTestResult(const SettingT&);
#endif
	
	void createUnit(const SettingT&);

	DegreesT m_unitDegreesVisibility;
	DistanceT m_unitDistanceVisibility;

	DataHolderT out;
};

