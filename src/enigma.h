#pragma once
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <imgui.h>

#include <string>
#include <functional>
#include <optional>
#include <vector>
#include <cstdint>
#include <iostream>

namespace Enigma {
    struct Config {
        std::string app_name = "";

        // Main window settings
        std::string app_title = ""; // the thing that show above the window
        uint16_t default_window_height = 0;
        uint16_t default_window_width = 0;
        bool force_default_window_size = false;
        bool no_console = false;
        bool maximized = false;

        // ImGui Config Flags (like enabling docking and multi viewports)
        int imgui_config_flags = ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable;

        // GLFW poll or wait
        enum GLFW_events { POLL, WAIT };
        GLFW_events poll_or_wait = WAIT;
        double wait_timeout = 0.;

        // Multiviewports focus behaviour
        bool viewports_focus_all = true;
        
        // DPI Aware
        bool DPI_aware = true;

        // JobScheduler settings
        uint8_t worker_pool_size = 1;
    };

    struct Animation {
        std::chrono::time_point<std::chrono::steady_clock> tp;
        long long int duration;
    };

    struct AppState {
        bool error = false;
        bool loop_running = false;
        bool before_frame = false;
        bool app_initialized = false;
        std::string error_msg = "";
        const char* glsl_version;
        float global_scaling = 0;

        // Monitors can be added, substracted, change their scaling
        // This is why we need to keep track if there is any change
        ImVector<float> monitors_scales;

        // Relative to rendering
        bool redraw = false;
        bool vsync = true;
        std::chrono::steady_clock::time_point poll_until;
        double wait_timeout;

        // Animation
        std::unordered_map<std::string, Animation> animations;
    };
    extern AppState app_state;

    class App {
    private:
        Config::GLFW_events m_glfw_poll_or_wait;
    protected:
        GLFWwindow* m_main_window;
    public: 
        App();
        virtual ~App() {}

        /**
         * @brief Implement this function if you want to call some flags
         * before the loop of the application is launched, but after ImGui
         * has been initialized
         */
        virtual void InitializationBeforeLoop() {}

        /**
         * @brief Implement this function if you want to finish gracefully
         * some functions
         */
        virtual void AfterLoop() {}

        /**
         * @brief This is where you want to put all the ImGui calls to draw the UI
         * This function is called each loop continuisly
         */
        virtual void FrameUpdate() {}
        /**
         * @brief Sometimes, some
         *
         */
        virtual void BeforeFrameUpdate() {}

        // Returns the main GLFW window
        GLFWwindow* GetWindow() { return m_main_window; }

        friend int Run(App* application, Config config);
    };

    /**
     * @brief Set the Multi Viewports Focus Behavior
     *
     * @param focus_all if true, if the user clicks on any window of the app,
     * then all window are focused. This can be used when one wants that the
     * whole program is shown when another program hides one or more windows.
     */
    void SetMultiViewportsFocusBehavior(bool focus_all);

    /**
     * @brief Replacement for ImGui::Begin to have multi-dpi awareness
     *
     * To be used with Tempo::End
     *
     * @param name
     * @param p_open
     * @param flags
     */
    void Begin(const char* name, bool* p_open = (bool*)0, ImGuiWindowFlags flags = 0);

    /**
     * @brief End of Tempo::Begin
     *
     */
    void End();

    /**
     * @brief If the application is set to Wait Events, then this will set a timeout
     * until the events are processed. If it is set to 0.0, then it is considered
     * that the application will wait until the next event.
     *
     * @param timeout timeout in seconds
     */
    void SetWaitTimeout(double timeout);

    /**
     * @brief If the application is set to Wait Events, then this will temporarily set the
     * application to Poll until the specified timer is expired
     *
     * @param seconds
     */
    void PollUntil(long long milliseconds);

    /**
     * @brief Activate or deactivate vsync during execution of the program
     *
     * @param vsync
     */
    void SetVSync(int interval);

    /**
     * @brief Returns the current DPI scaling of the main window
     *
     * @return float
     */
    float GetScaling();

    /**
     * @brief Pushes a new animation, which can be identified by name
     *
     * @param name of animation
     * @param duration in ms of the animation
     */
    void PushAnimation(const std::string& name, long long int duration);

    /**
     * @brief Get the animation progress
     *
     * @param name of animation
     * @return float progress (between 0 and 1) of the animation
     * if there is no animation in progress, it always returns 1.
     */
    float GetProgress(const std::string& name);

    int Run(App* application, Config config);
}