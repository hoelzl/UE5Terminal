# Contributing to UE5Terminal

Thank you for your interest in contributing to the UE5Terminal plugin!

## Getting Started

1. Fork the repository
2. Clone your fork locally
3. Create a new branch for your changes
4. Make your changes
5. Test your changes thoroughly
6. Submit a pull request

## Development Setup

1. **Prerequisites:**
   - Unreal Engine 5.0 or later
   - Visual Studio 2019/2022 (Windows) or Xcode (macOS)
   - Git

2. **Building the Plugin:**
   - Copy the `Plugins/Terminal` folder to your UE5 project's Plugins directory
   - Regenerate project files
   - Build the project

## Code Style

- Follow Unreal Engine coding standards
- Use tabs for indentation (matching UE5 style)
- Keep header files in `Public/` and implementation files in `Private/`
- Add copyright headers to all new files
- Document public APIs with comments

## Adding Features

When adding new features:

1. **Plan First**: Open an issue to discuss major changes
2. **Stay Focused**: Keep changes minimal and focused on one feature
3. **Document**: Update README.md with new features
4. **Examples**: Add examples to Content/Examples if applicable
5. **Test**: Ensure the plugin still compiles and works

## Testing

Since this is a UE5 plugin:

1. Test compilation on your target platforms
2. Test in both editor and packaged builds
3. Verify UMG widgets work in the UMG designer
4. Test CommonUI integration if modified
5. Test command history navigation
6. Test with various font sizes and history limits

## Pull Request Process

1. Update documentation for any API changes
2. Add your changes to the "Unreleased" section of a changelog (if one exists)
3. Ensure your code compiles without warnings
4. Write a clear PR description explaining your changes
5. Link any related issues

## Reporting Bugs

When reporting bugs, include:

- UE5 version
- Operating system
- Steps to reproduce
- Expected behavior
- Actual behavior
- Screenshots (if applicable)

## Feature Requests

Feature requests are welcome! Please:

- Explain the use case
- Describe the proposed solution
- Consider alternative approaches

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
