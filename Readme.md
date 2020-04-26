# **2020 OS Project 1** — Process Scheduling

### Environment

Ubuntu 16.04

CPUs: 4

Memory: 8192 MB

### Usage

```sh
make
./main < input.txt > output.txt
dmesg | grep Project1
```

### Utils

#### env.sh

- description: compile kernel 4.14.25

- usage:

  ```sh
  sh env.sh
  ```

#### main.py

- description: generate all stdout and dmesg file from input directory

- usage:

  ```sh
  python3 main.py input_directory main output_directory
  ```
#### theoretical.py

- description: generate all theoretical execution time file from input directory

- usage:

  ```sh
  gcc -o main main.c scheduler.c process.c CPU.c -D THEORETICAL
  python3 theoretical.py input_directory main theoretical_directory
  ```
#### diff_stdout_dmesg_order.py

- description: check the order between stdout and dmesg

- usage:

  ```sh
  python3 diff_stdout_dmesg_order.py input_directory output_directory
  ```
#### calculate_execute_unit_time.py

- description: check the unit time between output and theoretical

- usage:

  ```sh
  python3 calculate_execute_unit_time.py input_directory output_directory theoretical_directory
  ```
#### calculate_execute_unit_time_md.py

- description: check the unit time between output and theoretical and output markdown form

- usage:

  ```sh
  python3 calculate_execute_unit_time_md.py input_directory output_directory theoretical_directory
  ```