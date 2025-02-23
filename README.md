# STM32 Drivers Repository (Private - Semperonics Lab)

## Overview
Welcome to the **STM32 Drivers Repository**! This repository contains **bare-metal and HAL-based peripheral drivers** for STM32 microcontrollers, organized systematically for easy navigation and usage. It includes UART, SPI, I2C, and GPIO drivers, with **CMSIS and HAL implementations**, along with test examples and documentation.

## Repository Structure

```
📦 stm32-drivers-repo
│
├── 📂 main/                      # Main branch (Overview & Documentation)
│   ├── 📜 README.md               # Explains the entire repo structure
│   ├── 📜 PERIPHERALS.md          # List of all peripherals and links to branches
│   ├── 📜 GIT_TUTORIAL.md         # Complete Git learning section
│   ├── 📜 STM32_IDE_GIT.md        # Guide on STM32CubeIDE + Eclipse + Git
│
├── 📂 UART/                      # UART Peripheral Driver Branch
│   ├── 📂 HAL_UART/               # HAL-based UART driver
│   ├── 📂 CMSIS_UART/             # CMSIS-based UART driver
│
├── 📂 SPI/                       # SPI Peripheral Driver Branch
│   ├── 📂 HAL_SPI/                # HAL-based SPI driver
│   ├── 📂 CMSIS_SPI/              # CMSIS-based SPI driver
│
├── 📂 I2C/                       # I2C Peripheral Driver Branch
│   ├── 📂 HAL_I2C/                # HAL-based I2C driver
│   ├── 📂 CMSIS_I2C/              # CMSIS-based I2C driver
│
├── 📂 GPIO/                      # GPIO Peripheral Driver Branch
│   ├── 📂 HAL_GPIO/               # HAL-based GPIO driver
│   ├── 📂 CMSIS_GPIO/             # CMSIS-based GPIO driver
│
├── 📂 docs/                      # Documentation Section
├── 📂 examples/                  # Test Code for Each Peripheral
├── 📂 tools/                     # Development Tools & Scripts
├── 📜 .gitignore                 # Ignore build files
├── 📜 README.md                  # Main repository description
```

## Features
- **HAL & CMSIS-Based Drivers:** Implementations using STM32 HAL and CMSIS for optimized performance.
- **Peripheral Drivers:** Includes UART, SPI, I2C, and GPIO drivers with examples.
- **IC-Specific Implementations:** Separate drivers for STM32F103, STM32F401, and STM32F407.
- **Documentation:** Step-by-step guides for STM32 development, including Git tutorials and STM32CubeIDE integration.
- **Development Tools:** Scripts for setting up the environment and debugging.

## Access & Security
This repository is **private** and accessible only to **Semperonics Lab members**. Unauthorized access or distribution of this code is strictly prohibited. 

### Access Policy
- **Only approved team members** have access.
- **Forking is disabled** to maintain repository integrity.
- **External contributions require explicit approval** from the repository maintainers.

## Getting Started
### Prerequisites
- **STM32CubeIDE** or **Keil/ARM Compiler**
- **Git** for version control
- **Python** (for debugging scripts)

### Cloning the Repository
```sh
 git clone  https://github.com/Sathwikpb/Driver_CMSIS_BM_F103xb.git
 cd stm32-drivers-repo
```

### Running Example Code
Each peripheral has test examples in the `examples/` directory. To test UART:
```sh
 cd examples/
 open uart_test.c in STM32CubeIDE
 compile & upload to your STM32 board
```

## Contribution Guidelines
### Internal Contributions (Semperonics Lab Members)
1. **Create a branch** for your feature.
2. **Commit your changes** with proper documentation.
3. **Push to GitHub** and create a pull request.
4. **Get approval** from the repository maintainers.

### External Contributions
- External contributions require approval from the **Semperonics Lab Admin Team**.
- Contact the maintainers before submitting any pull requests.

## License
This project is **proprietary** and restricted to **Semperonics Lab** use only. Unauthorized sharing, copying, or distribution is prohibited.

## Contact
For any queries, issues, or access requests, contact the **Semperonics Lab Admin Team** or open an internal issue.

