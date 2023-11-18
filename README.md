## Computer Science Roadmap

This repository has C implementations of the [Computer Science Roadmap](https://roadmap.sh/computer-science) topics.

### How to run the code?

You need to have gcc installed.

```sh
git clone https://github.com/AndreyArthur/computer-science-roadmap-c

cd ./computer-science-roadmap-c

chmod +x ./scripts/run ./scripts/test
```

If `main.c` file exists, running `./scripts/run` will execute it. If `main.c` does not exist it will create the file that prints a "Hello, World!" message and execute it.

`./scripts/test <path_to_test_file.c>` will execute given test file if it exists, and return an error if it does not exist.

***Note that these scripts should only work in the base directory of this repository.***
