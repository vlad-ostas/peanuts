from conan import ConanFile

class PeanutsRecepe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("glfw/3.4")
        self.requires("glad/0.1.36")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.13]") # NOTE(Akumanory): Inside [] is a version range

    # Example
    # For more config params please refer: 
    # https://conan.io/center/recipes/glfw
    # And go to the package section
    # def configure(self):
    #     self.options["glfw/*"].fPIC = True

