#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QObject>
#include <QByteArrayList>
#include <QSize>
#include <QKeySequence>
#include <QMultiMap>

#include "events.h"

// In both versions the default new map border is a generic tree
#define DEFAULT_BORDER_RSE (QList<uint16_t>{0x1D4, 0x1D5, 0x1DC, 0x1DD})
#define DEFAULT_BORDER_FRLG (QList<uint16_t>{0x14, 0x15, 0x1C, 0x1D})

#define CONFIG_BACKWARDS_COMPATABILITY

enum MapSortOrder {
    Group   =  0,
    Area    =  1,
    Layout  =  2,
};

class KeyValueConfigBase
{
public:
    void save();
    void load();
    void setSaveDisabled(bool disabled);
    virtual ~KeyValueConfigBase();
    virtual void reset() = 0;
protected:
    virtual QString getConfigFilepath() = 0;
    virtual void parseConfigKeyValue(QString key, QString value) = 0;
    virtual QMap<QString, QString> getKeyValueMap() = 0;
    virtual void onNewConfigFileCreated() = 0;
    virtual void setUnreadKeys() = 0;
    bool getConfigBool(QString key, QString value);
    int getConfigInteger(QString key, QString value, int min = INT_MIN, int max = INT_MAX, int defaultValue = 0);
    uint32_t getConfigUint32(QString key, QString value, uint32_t min = 0, uint32_t max = UINT_MAX, uint32_t defaultValue = 0);
private:
    bool saveDisabled = false;
};

class PorymapConfig: public KeyValueConfigBase
{
public:
    PorymapConfig() {
        reset();
    }
    virtual void reset() override {
        this->recentProject = "";
        this->reopenOnLaunch = true;
        this->mapSortOrder = MapSortOrder::Group;
        this->prettyCursors = true;
        this->collisionOpacity = 50;
        this->collisionZoom = 30;
        this->metatilesZoom = 30;
        this->showPlayerView = false;
        this->showCursorTile = true;
        this->showBorder = true;
        this->showGrid = false;
        this->monitorFiles = true;
        this->tilesetCheckerboardFill = true;
        this->theme = "default";
        this->textEditorOpenFolder = "";
        this->textEditorGotoLine = "";
        this->paletteEditorBitDepth = 24;
        this->projectSettingsTab = 0;
    }
    void setRecentProject(QString project);
    void setReopenOnLaunch(bool enabled);
    void setMapSortOrder(MapSortOrder order);
    void setPrettyCursors(bool enabled);
    void setMainGeometry(QByteArray, QByteArray, QByteArray, QByteArray);
    void setTilesetEditorGeometry(QByteArray, QByteArray);
    void setPaletteEditorGeometry(QByteArray, QByteArray);
    void setRegionMapEditorGeometry(QByteArray, QByteArray);
    void setProjectSettingsEditorGeometry(QByteArray, QByteArray);
    void setCustomScriptsEditorGeometry(QByteArray, QByteArray);
    void setCollisionOpacity(int opacity);
    void setCollisionZoom(int zoom);
    void setMetatilesZoom(int zoom);
    void setShowPlayerView(bool enabled);
    void setShowCursorTile(bool enabled);
    void setShowBorder(bool enabled);
    void setShowGrid(bool enabled);
    void setMonitorFiles(bool monitor);
    void setTilesetCheckerboardFill(bool checkerboard);
    void setTheme(QString theme);
    void setTextEditorOpenFolder(const QString &command);
    void setTextEditorGotoLine(const QString &command);
    void setPaletteEditorBitDepth(int bitDepth);
    void setProjectSettingsTab(int tab);
    QString getRecentProject();
    bool getReopenOnLaunch();
    MapSortOrder getMapSortOrder();
    bool getPrettyCursors();
    QMap<QString, QByteArray> getMainGeometry();
    QMap<QString, QByteArray> getTilesetEditorGeometry();
    QMap<QString, QByteArray> getPaletteEditorGeometry();
    QMap<QString, QByteArray> getRegionMapEditorGeometry();
    QMap<QString, QByteArray> getProjectSettingsEditorGeometry();
    QMap<QString, QByteArray> getCustomScriptsEditorGeometry();
    int getCollisionOpacity();
    int getCollisionZoom();
    int getMetatilesZoom();
    bool getShowPlayerView();
    bool getShowCursorTile();
    bool getShowBorder();
    bool getShowGrid();
    bool getMonitorFiles();
    bool getTilesetCheckerboardFill();
    QString getTheme();
    QString getTextEditorOpenFolder();
    QString getTextEditorGotoLine();
    int getPaletteEditorBitDepth();
    int getProjectSettingsTab();
protected:
    virtual QString getConfigFilepath() override;
    virtual void parseConfigKeyValue(QString key, QString value) override;
    virtual QMap<QString, QString> getKeyValueMap() override;
    virtual void onNewConfigFileCreated() override {};
    virtual void setUnreadKeys() override {};
private:
    QString recentProject;
    bool reopenOnLaunch;
    QString stringFromByteArray(QByteArray);
    QByteArray bytesFromString(QString);
    MapSortOrder mapSortOrder;
    bool prettyCursors;
    QByteArray mainWindowGeometry;
    QByteArray mainWindowState;
    QByteArray mapSplitterState;
    QByteArray eventsSlpitterState;
    QByteArray mainSplitterState;
    QByteArray tilesetEditorGeometry;
    QByteArray tilesetEditorState;
    QByteArray paletteEditorGeometry;
    QByteArray paletteEditorState;
    QByteArray regionMapEditorGeometry;
    QByteArray regionMapEditorState;
    QByteArray projectSettingsEditorGeometry;
    QByteArray projectSettingsEditorState;
    QByteArray customScriptsEditorGeometry;
    QByteArray customScriptsEditorState;
    int collisionOpacity;
    int collisionZoom;
    int metatilesZoom;
    bool showPlayerView;
    bool showCursorTile;
    bool showBorder;
    bool showGrid;
    bool monitorFiles;
    bool tilesetCheckerboardFill;
    QString theme;
    QString textEditorOpenFolder;
    QString textEditorGotoLine;
    int paletteEditorBitDepth;
    int projectSettingsTab;
};

extern PorymapConfig porymapConfig;

enum BaseGameVersion {
    pokeruby,
    pokefirered,
    pokeemerald,
};

enum ProjectFilePath {
    data_map_folders,
    data_scripts_folders,
    data_layouts_folders,
    data_tilesets_folders,
    data_event_scripts,
    json_map_groups,
    json_layouts,
    json_wild_encounters,
    json_region_map_entries,
    json_region_porymap_cfg,
    tilesets_headers,
    tilesets_graphics,
    tilesets_metatiles,
    tilesets_headers_asm,
    tilesets_graphics_asm,
    tilesets_metatiles_asm,
    data_obj_event_gfx_pointers,
    data_obj_event_gfx_info,
    data_obj_event_pic_tables,
    data_obj_event_gfx,
    data_pokemon_gfx,
    data_heal_locations,
    constants_global,
    constants_map_groups,
    constants_items,
    constants_flags,
    constants_vars,
    constants_weather,
    constants_songs,
    constants_heal_locations,
    constants_pokemon,
    constants_map_types,
    constants_trainer_types,
    constants_secret_bases,
    constants_obj_event_movement,
    constants_obj_events,
    constants_event_bg,
    constants_region_map_sections,
    constants_metatile_labels,
    constants_metatile_behaviors,
    constants_species,
    constants_fieldmap,
    global_fieldmap,
    fieldmap,
    initial_facing_table,
    pokemon_icon_table,
    pokemon_gfx,
};

class ProjectConfig: public KeyValueConfigBase
{
public:
    ProjectConfig() {
        reset();
    }
    virtual void reset() override {
        this->baseGameVersion = BaseGameVersion::pokeemerald;
        // Reset non-version-specific settings
        this->usePoryScript = false;
        this->enableTripleLayerMetatiles = false;
        this->defaultMetatileId = 1;
        this->defaultElevation = 3;
        this->defaultCollision = 0;
        this->defaultPrimaryTileset = "gTileset_General";
        this->prefabFilepath = QString();
        this->prefabImportPrompted = false;
        this->tilesetsHaveCallback = true;
        this->tilesetsHaveIsCompressed = true;
        this->filePaths.clear();
        this->eventIconPaths.clear();
        this->pokemonIconPaths.clear();
        this->collisionSheetPath = QString();
        this->collisionSheetWidth = 2;
        this->collisionSheetHeight = 16;
        this->blockMetatileIdMask = 0x03FF;
        this->blockCollisionMask = 0x0C00;
        this->blockElevationMask = 0xF000;
        this->readKeys.clear();
    }
    static const QMap<ProjectFilePath, std::pair<QString, QString>> defaultPaths;
    static const QStringList versionStrings;
    void reset(BaseGameVersion baseGameVersion);
    void setBaseGameVersion(BaseGameVersion baseGameVersion);
    BaseGameVersion getBaseGameVersion();
    QString getBaseGameVersionString();
    QString getBaseGameVersionString(BaseGameVersion version);
    BaseGameVersion stringToBaseGameVersion(QString string, bool * ok = nullptr);
    void setUsePoryScript(bool usePoryScript);
    bool getUsePoryScript();
    void setProjectDir(QString projectDir);
    QString getProjectDir();
    void setUseCustomBorderSize(bool enable);
    bool getUseCustomBorderSize();
    void setEventWeatherTriggerEnabled(bool enable);
    bool getEventWeatherTriggerEnabled();
    void setEventSecretBaseEnabled(bool enable);
    bool getEventSecretBaseEnabled();
    void setHiddenItemQuantityEnabled(bool enable);
    bool getHiddenItemQuantityEnabled();
    void setHiddenItemRequiresItemfinderEnabled(bool enable);
    bool getHiddenItemRequiresItemfinderEnabled();
    void setHealLocationRespawnDataEnabled(bool enable);
    bool getHealLocationRespawnDataEnabled();
    void setEventCloneObjectEnabled(bool enable);
    bool getEventCloneObjectEnabled();
    void setFloorNumberEnabled(bool enable);
    bool getFloorNumberEnabled();
    void setCreateMapTextFileEnabled(bool enable);
    bool getCreateMapTextFileEnabled();
    void setTripleLayerMetatilesEnabled(bool enable);
    bool getTripleLayerMetatilesEnabled();
    int getNumLayersInMetatile();
    int getNumTilesInMetatile();
    void setDefaultMetatileId(uint16_t metatileId);
    uint16_t getDefaultMetatileId();
    void setDefaultElevation(int elevation);
    int getDefaultElevation();
    void setDefaultCollision(int collision);
    int getDefaultCollision();
    void setNewMapBorderMetatileIds(QList<uint16_t> metatileIds);
    QList<uint16_t> getNewMapBorderMetatileIds();
    QString getDefaultPrimaryTileset();
    QString getDefaultSecondaryTileset();
    void setDefaultPrimaryTileset(QString tilesetName);
    void setDefaultSecondaryTileset(QString tilesetName);
    void setFilePath(QString pathId, QString path);
    void setFilePath(ProjectFilePath pathId, QString path);
    QString getFilePath(QString defaultPath, bool customOnly = false);
    QString getFilePath(ProjectFilePath pathId, bool customOnly = false);
    void setPrefabFilepath(QString filepath);
    QString getPrefabFilepath();
    void setPrefabImportPrompted(bool prompted);
    bool getPrefabImportPrompted();
    void setTilesetsHaveCallback(bool has);
    bool getTilesetsHaveCallback();
    void setTilesetsHaveIsCompressed(bool has);
    bool getTilesetsHaveIsCompressed();
    int getMetatileAttributesSize();
    void setMetatileAttributesSize(int size);
    uint32_t getMetatileBehaviorMask();
    uint32_t getMetatileTerrainTypeMask();
    uint32_t getMetatileEncounterTypeMask();
    uint32_t getMetatileLayerTypeMask();
    void setMetatileBehaviorMask(uint32_t mask);
    void setMetatileTerrainTypeMask(uint32_t mask);
    void setMetatileEncounterTypeMask(uint32_t mask);
    void setMetatileLayerTypeMask(uint32_t mask);
    uint16_t getBlockMetatileIdMask();
    uint16_t getBlockCollisionMask();
    uint16_t getBlockElevationMask();
    void setBlockMetatileIdMask(uint16_t mask);
    void setBlockCollisionMask(uint16_t mask);
    void setBlockElevationMask(uint16_t mask);
    bool getMapAllowFlagsEnabled();
    void setMapAllowFlagsEnabled(bool enabled);
    void setEventIconPath(Event::Group group, const QString &path);
    QString getEventIconPath(Event::Group group);
    void setPokemonIconPath(const QString &species, const QString &path);
    QString getPokemonIconPath(const QString & species);
    QHash<QString, QString> getPokemonIconPaths();
    void setCollisionSheetPath(const QString &path);
    QString getCollisionSheetPath();
    void setCollisionSheetWidth(int width);
    int getCollisionSheetWidth();
    void setCollisionSheetHeight(int height);
    int getCollisionSheetHeight();

    // TODO: Replace these once there's generic support for editing project names
    static const QString metatileIdMaskName;
    static const QString collisionMaskName;
    static const QString elevationMaskName;
    static const QString behaviorMaskName;
    static const QString layerTypeMaskName;
    static const QString behaviorTableName;
    static const QString layerTypeTableName;
    static const QString terrainTypeTableName;
    static const QString encounterTypeTableName;
    static const QString attrTableName;

protected:
    virtual QString getConfigFilepath() override;
    virtual void parseConfigKeyValue(QString key, QString value) override;
    virtual QMap<QString, QString> getKeyValueMap() override;
    virtual void onNewConfigFileCreated() override;
    virtual void setUnreadKeys() override;
private:
    BaseGameVersion baseGameVersion;
    QString projectDir;
    QMap<ProjectFilePath, QString> filePaths;
    bool usePoryScript;
    bool useCustomBorderSize;
    bool enableEventWeatherTrigger;
    bool enableEventSecretBase;
    bool enableHiddenItemQuantity;
    bool enableHiddenItemRequiresItemfinder;
    bool enableHealLocationRespawnData;
    bool enableEventCloneObject;
    bool enableFloorNumber;
    bool createMapTextFile;
    bool enableTripleLayerMetatiles;
    uint16_t defaultMetatileId;
    uint16_t defaultElevation;
    uint16_t defaultCollision;
    QList<uint16_t> newMapBorderMetatileIds;
    QString defaultPrimaryTileset;
    QString defaultSecondaryTileset;
    QStringList readKeys;
    QString prefabFilepath;
    bool prefabImportPrompted;
    bool tilesetsHaveCallback;
    bool tilesetsHaveIsCompressed;
    int metatileAttributesSize;
    uint32_t metatileBehaviorMask;
    uint32_t metatileTerrainTypeMask;
    uint32_t metatileEncounterTypeMask;
    uint32_t metatileLayerTypeMask;
    uint16_t blockMetatileIdMask;
    uint16_t blockCollisionMask;
    uint16_t blockElevationMask;
    bool enableMapAllowFlags;
    QMap<Event::Group, QString> eventIconPaths;
    QHash<QString, QString> pokemonIconPaths;
    QString collisionSheetPath;
    int collisionSheetWidth;
    int collisionSheetHeight;
};

extern ProjectConfig projectConfig;

class UserConfig: public KeyValueConfigBase
{
public:
    UserConfig() {
        reset();
    }
    virtual void reset() override {
        this->recentMap = QString();
        this->useEncounterJson = true;
        this->customScripts.clear();
        this->readKeys.clear();
    }
    void setRecentMap(const QString &map);
    QString getRecentMap();
    void setEncounterJsonActive(bool active);
    bool getEncounterJsonActive();
    void setProjectDir(QString projectDir);
    QString getProjectDir();
    void setCustomScripts(QStringList scripts, QList<bool> enabled);
    QStringList getCustomScriptPaths();
    QList<bool> getCustomScriptsEnabled();
    void parseCustomScripts(QString input);
    QString outputCustomScripts();
protected:
    virtual QString getConfigFilepath() override;
    virtual void parseConfigKeyValue(QString key, QString value) override;
    virtual QMap<QString, QString> getKeyValueMap() override;
    virtual void onNewConfigFileCreated() override;
    virtual void setUnreadKeys() override;
#ifdef CONFIG_BACKWARDS_COMPATABILITY
    friend class ProjectConfig;
#endif    
private:
    QString projectDir;
    QString recentMap;
    bool useEncounterJson;
    QMap<QString, bool> customScripts;
    QStringList readKeys;
};

extern UserConfig userConfig;

class QAction;
class Shortcut;

class ShortcutsConfig : public KeyValueConfigBase
{
public:
    ShortcutsConfig() :
        user_shortcuts({ }),
        default_shortcuts({ })
    { }

    virtual void reset() override { user_shortcuts.clear(); }

    // Call this before applying user shortcuts so that the user can restore defaults.
    void setDefaultShortcuts(const QObjectList &objects);
    QList<QKeySequence> defaultShortcuts(const QObject *object) const;

    void setUserShortcuts(const QObjectList &objects);
    void setUserShortcuts(const QMultiMap<const QObject *, QKeySequence> &objects_keySequences);
    QList<QKeySequence> userShortcuts(const QObject *object) const;

protected:
    virtual QString getConfigFilepath() override;
    virtual void parseConfigKeyValue(QString key, QString value) override;
    virtual QMap<QString, QString> getKeyValueMap() override;
    virtual void onNewConfigFileCreated() override { };
    virtual void setUnreadKeys() override { };

private:
    QMultiMap<QString, QKeySequence> user_shortcuts;
    QMultiMap<QString, QKeySequence> default_shortcuts;

    enum StoreType {
        User,
        Default
    };

    QString cfgKey(const QObject *object) const;
    QList<QKeySequence> currentShortcuts(const QObject *object) const;

    void storeShortcutsFromList(StoreType storeType, const QObjectList &objects);
    void storeShortcuts(
            StoreType storeType,
            const QString &cfgKey,
            const QList<QKeySequence> &keySequences);
};

extern ShortcutsConfig shortcutsConfig;

#endif // CONFIG_H
