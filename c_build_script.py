# -------------------------------- GENERATED BY C_BUILD --------------------------------
import os
import sys

def FIND_C_BUILD(current_dir):
    if os.path.isdir(os.path.join(current_dir, "c_build")):
        sys.path.insert(0, current_dir)
        return

    parent_dir = os.path.dirname(current_dir)
    if parent_dir != current_dir:
        FIND_C_BUILD(parent_dir)

FIND_C_BUILD(os.path.abspath(os.path.dirname(__file__)))
from c_build.source.UserUtilities import *
from c_build.source.Manager import *
# --------------------------------------------------------------------------------------s

cc: CompilerConfig = CompilerConfig(
    compiler_name = C_BUILD_COMPILER_NAME() if C_BUILD_IS_DEPENDENCY() else "INVALID_COMPILER",
)

pc: ProjectConfig = ProjectConfig(
    project_name = "IOD",
    project_dependencies = [],
    project_debug_with_visual_studio = True,
    project_executable_names = ["glfw_test.exe"]
)

if IS_WINDOWS() and not C_BUILD_IS_DEPENDENCY():
    cc.compiler_name = "cl"
elif IS_DARWIN() and not C_BUILD_IS_DEPENDENCY():
    cc.compiler_name = "clang"
elif IS_LINUX() and not C_BUILD_IS_DEPENDENCY():
    cc.compiler_name = "gcc"

# Do different things depending on the platform
if cc.compiler_name == "cl":
    cc.compiler_warning_level = "3"
    cc.compiler_disable_specific_warnings = ["5105", "4668", "4820", "4996"]
else:
    cc.compiler_warning_level = "all"
    cc.compiler_disable_specific_warnings = ["deprecated", "parentheses"]


build_postfix = f"build_{cc.compiler_name}/{C_BUILD_BUILD_TYPE()}"
procedures: Dict[str, ProcedureConfig] = {
    "IOD Library": ProcedureConfig(
        build_directory=f"./{build_postfix}",
        output_name= GET_LIB_NAME(cc, "IOD"),
        source_files=["../../*.cpp"],
        include_paths=["../../", "../../libs"],
    )
}

manager: Manager = Manager(cc, pc, procedures)
manager.build_project()
