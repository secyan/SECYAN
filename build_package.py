from re import sub
import inquirer
import shutil
import subprocess


def clean():
    print("Start cleaning process")
    shutil.rmtree("dist", ignore_errors=True)
    shutil.rmtree("build", ignore_errors=True)


def build():
    print("Start build process")
    subprocess.check_call(["python3", "-m", "build"])


def upload():
    print("Start upload process")
    subprocess.check_call(["python3", "-m", "twine", "upload", "dist/*"])


questions = [
    inquirer.List(
        "clean",
        message="Do you want to clean the project before building process?",
        choices=["yes", "no"]),

    inquirer.List(
        "build",
        message="Do you want to build the project now?",
        choices=["yes", "no"],
    ),
    inquirer.List(
        "upload",
        message="Do you want to upload the build files?",
        choices=["yes", "no"],
    )
]

processes = [
    clean,
    build,
    upload,
]

for i, question in enumerate(questions):
    process = processes[i]
    answer = inquirer.prompt([question])
    for key, value in answer.items():
        if value == "yes":
            process()
