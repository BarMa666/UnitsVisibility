#pragma once
#include "Types.h"

class Unit;

class UnitSettings
{
public:
	using DegreesT = float;
	using DistanceT = int;
	using SettingT = std::wstring;

	static UnitSettings& instance();

	void loadSettings();

	UnitSettings(const UnitSettings&) = delete;
	UnitSettings& operator=(const UnitSettings&) = delete;
	UnitSettings(UnitSettings&&) = delete;
	UnitSettings& operator=(UnitSettings&&) = delete;

	DegreesT getDegreesVisibility() const;
	DistanceT getDistanceVisibility() const;

private:
	UnitSettings();

	void setupSetting(const SettingT&);
	DegreesT setupDegreesVisibility(const SettingT&);
	DistanceT setupDistanceVisibility(const SettingT&);

	NameT setupName(const SettingT&);
	PositionT setupPosition(const SettingT&);
	DirectionT setupDirection(const SettingT&);
	
	void createUnit(const SettingT&);

	DegreesT m_unitDegreesVisibility;
	DistanceT m_unitDistanceVisibility;
};

