#pragma once
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace nlohmann
{
    template <typename, typename> struct adl_serializer;
} // namespace nlohmann

namespace Soundux
{
    namespace Objects
    {
        struct AudioDevice;

        enum class ErrorCode : std::uint8_t
        {
            FailedToPlay,
            FailedToSeek,
            FailedToPause,
            FailedToRepeat,
            FailedToResume,
            FailedToMoveToSink,
            SoundNotFound,
            FolderDoesNotExist,
            TabDoesNotExist,
            FailedToSetHotkey,
            FailedToStartPassthrough,
            FailedToMoveBack,
            FailedToMoveBackPassthrough,
            FailedToRevertDefaultSource,
            FailedToSetDefaultSource,
            YtdlNotFound,
            YtdlInvalidUrl,
            YtdlInvalidJson,
            YtdlInformationUnknown,
            FailedToDelete
        };

        enum class SortMode : std::uint8_t
        {
            ModifiedDate_Ascending,
            ModifiedDate_Descending,
            Alphabetical_Ascending,
            Alphabetical_Descending,
        };

        enum class Theme : std::uint8_t
        {
            System,
            Dark,
            Light
        };

        enum class ViewMode : std::uint8_t
        {
            List,
            Grid,
            EmulatedLaunchpad,
        };

        enum class BackendType : std::uint8_t
        {
            PulseAudio,
            PipeWire,
        };

        struct Sound
        {
            std::uint32_t id;
            std::string name;
            std::string path;
            bool isFavorite = false;

            std::vector<int> hotkeys;
            std::uint64_t modifiedDate;
        };
        struct Tab
        {
            std::uint32_t id; //* Equal to index
            std::string name;
            std::string path;

            std::vector<Sound> sounds;
        };

        class SettingBase
        {
          protected:
            bool state;
            std::vector<int> hotKey;

          public:
            void toggle();
            bool enabled() const;
            const std::vector<int> &hotkey() const;

            virtual ~SettingBase() = default;
            static inline std::vector<SettingBase *> settings;
        };
        template <typename T> class HotkeySetting : public SettingBase
        {
            template <typename, typename> friend struct nlohmann::adl_serializer;

            T value;

          public:
            T &get()
            {
                return value;
            }
            operator T &()
            {
                return value;
            }
            operator const T &() const
            {
                return value;
            }

            HotkeySetting() = default;
            HotkeySetting(const T &value) : value(value) {}
        };

        struct Settings
        {
            SortMode sortMode = SortMode::ModifiedDate_Descending;
            BackendType audioBackend = BackendType::PulseAudio;
            ViewMode viewMode = ViewMode::List;
            Theme theme = Theme::System;

            HotkeySetting<std::vector<int>> pushToTalkKeys;
            HotkeySetting<bool> muteDuringPlayback = false;
            HotkeySetting<bool> allowOverlapping = true;
            HotkeySetting<bool> tabHotkeysOnly = false;

            std::vector<int> stopHotkey;

            std::uint32_t selectedTab = 0;
            std::string output;

            float remoteVolume = 1.f;
            float localVolume = 0.5f;
            bool syncVolumes = false;

            bool useAsDefaultDevice = false;
            bool minimizeToTray = false;
            bool deleteToTrash = true;

            void setup();
        };
        class Data
        {
            template <typename, typename> friend struct nlohmann::adl_serializer;

          private:
            std::vector<Tab> tabs;

          public:
            bool isOnFavorites = false;
            int width = 1280, height = 720;
            std::uint32_t soundIdCounter = 0;

            std::vector<Tab> getTabs() const;
            void setTabs(const std::vector<Tab> &);
            std::optional<Tab> setTab(const std::uint32_t &, const Tab &);

            Tab addTab(Tab);
            void removeTabById(const std::uint32_t &);

            std::optional<Tab> getTab(const std::uint32_t &) const;
            std::optional<std::reference_wrapper<Sound>> getSound(const std::uint32_t &);

            std::vector<Sound> getFavorites();
            std::vector<std::uint32_t> getFavoriteIds();
            void markFavorite(const std::uint32_t &, bool);

            void set(const Data &other);
            Data &operator=(const Data &other) = delete;
        };
    } // namespace Objects
} // namespace Soundux