from os import scandir, rename
from os.path import splitext, exists, join
from shutil import move
from time import sleep
import os
import logging

from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

source_dir = "/home/vivekup3424/Documents/IIITM_Gwalior/Sem_4/ACP/cses/leetcode"
cpp_dir = "/home/vivekup3424/Documents/IIITM_Gwalior/Sem_4/ACP/cses/leetcode/cpp"
python_dir = "/home/vivekup3424/Documents/IIITM_Gwalior/Sem_4/ACP/cses/leetcode/python"
go_dir = "/home/vivekup3424/Documents/IIITM_Gwalior/Sem_4/ACP/cses/leetcode/go"

with os.scandir(source_dir) as entries:
    for entry in entries:
        print(entry.name)

python_extensions = [".py",".ipynb"]

go_extensions = [".go"]

cpp_extensions = [".c",".cpp"]



def make_unique(dest, name):
    filename, extension = splitext(name)
    counter = 1
    # * IF FILE EXISTS, ADDS NUMBER TO THE END OF THE FILENAME
    while exists(f"{dest}/{name}"):
        name = f"{filename}({str(counter)}){extension}"
        counter += 1

    return name


def move_file(dest, entry, name):
    if exists(f"{dest}/{name}"):
        unique_name = make_unique(dest, name)
        oldName = join(dest, name)
        newName = join(dest, unique_name)
        rename(oldName, newName)
    move(entry, dest)

class MoverHandler(FileSystemEventHandler):
    # ? THIS FUNCTION WILL RUN WHENEVER THERE IS A CHANGE IN "source_dir"
    # ? .upper is for not missing out on files with uppercase extensions
    def on_modified(self, event):
        with scandir(source_dir) as entries:
            for entry in entries:
                name = entry.name
                self.check_python_files(entry, name)
                self.go(entry, name)
                self.check_cpp_files(entry, name)

    def check_python_files(self, entry, name):  # * Checks all Python Files
        for py_extension in python_extensions:
            if name.endswith(py_extension) or name.endswith(py_extension.upper()):
                move_file(python_dir, entry, name)
                logging.info(f"Moved python file: {name}")

    def go(self, entry, name):  # * Checks all go Files
        for go_extension in go_extensions:
            if name.endswith(go_extension) or name.endswith(go_extension.upper()):
                move_file(go_dir, entry, name)
                logging.info(f"Moved go file: {name}")

    def check_cpp_files(self, entry, name):  # * Checks all Image Files
        for cpp_extension in cpp_extensions:
            if name.endswith(cpp_extension) or name.endswith(cpp_extension.upper()):
                move_file(cpp_dir,entry, name)
                logging.info(f"Moved image file: {name}")


#watchdog template code
if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO,
                        format='%(asctime)s - %(message)s',
                        datefmt='%Y-%m-%d %H:%M:%S')
    path = source_dir
    event_handler = MoverHandler()
    observer = Observer()
    observer.schedule(event_handler, path, recursive=True)
    observer.start()
    try:
        while True:
            sleep(10)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()