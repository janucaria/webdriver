import os
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, cmake_layout

class WebdriverConan(ConanFile):
    name = "Webdriver"
    version = "0.1"

    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {"shared": False, "fPIC": True}
    exports_sources = "CMakeLists.txt", "sources/*"
    
    requires = [
        "gtest/1.11.0",
        "nlohmann_json/3.11.2",
        "fmt/9.1.0",
        "cpp-httplib/0.11.2"
    ]

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)
        self.folders.generators = os.path.join("conan", "generators")

    def generate(self):
        cmake_deps = CMakeDeps(self)
        cmake_deps.generate()

        cmake_tc = CMakeToolchain(self)
        cmake_tc.user_presets_path = False
        cmake_tc.generator = "Ninja Multi-Config"
        cmake_tc.variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        cmake_tc.generate()
