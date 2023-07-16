import argparse
import subprocess
import sys
import shlex


def err_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def print_run_command(command):
    err_print("run command: {}".format(shlex.join(command)))


def exec_conan_install(build_missing, build_type):
    command = ["conan",
               "install", ".",
               "--update",
               "--install-folder=build/conan/install",
               "--output-folder=build",
               "--profile=default"
               ]

    if build_missing:
        command.append("--build=missing")

    command.extend(["--settings", "build_type={}".format(build_type)])

    print_run_command(command)
    process_result = subprocess.run(command,
                                    universal_newlines=True)
    err_print("")

    return process_result.returncode


def run_prepare_deps(args):
    is_release = args.release
    is_build_missing = args.build_missing

    conan_build_type = "Release" if is_release else "Debug"

    return_code = exec_conan_install(is_build_missing, conan_build_type)
    if return_code:
        return return_code

    err_print("Prepare dependencies success\n")
    err_print("To setup vcvars: \".\\build\\conan\\generators\\conanbuild.bat\"")
    
    return return_code


def init_argparse() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers()

    configure_parser = subparsers.add_parser("prepare-deps")
    configure_parser.add_argument(
        "--build-missing",
        dest="build_missing",
        action="store_true",
        help="use the package if missing"
    )
    configure_parser.add_argument(
        "--release",
        dest="release",
        action="store_true",
        help="use release config"
    )
    configure_parser.set_defaults(handler=run_prepare_deps)

    return parser


def main() -> int:
    parser = init_argparse()
    args = parser.parse_args()

    if (args.handler != None):
        return args.handler(args)

    return 0


if __name__ == "__main__":
    error_code = main()
    sys.exit(error_code)
