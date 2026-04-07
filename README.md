# nmclean (Node Modules Cleaner)

[![npm version](https://badge.fury.io/js/nmclean.svg)](https://badge.fury.io/js/nmclean)
[![downloads](https://img.shields.io/npm/dy/nmclean.svg)](https://www.npmjs.com/package/nmclean)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/mdsiaofficial/nmclean/blob/main/LICENSE) 
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://nmclean.vervel.app/how-to-contribute.html#your-first-pull-request)


A simple and efficient Node.js CLI tool to recursively find and delete `node_modules` directories from your project and its subdirectories.

## Description

`nmclean` is designed to help developers clean up their projects by removing all `node_modules` folders. It starts from the current working directory and recursively searches through all subdirectories to locate and delete any `node_modules` directories it finds. This is particularly useful for freeing up disk space or preparing a project for archiving/deployment.

## Installation

Install globally via npm:

```bash
npm install -g nmclean
```

Or run directly with npx:

```bash
npx nmclean
```

## Usage

After installation, simply run the command in your project directory:

```bash
nmclean
```

The tool will:
1. Start scanning from the current working directory
2. Recursively search all subdirectories
3. Delete any `node_modules` folders found
4. Display progress with colored output
5. Handle permission errors gracefully

### Example Output

```
--- Node Modules Cleaner (nmclean) ---
Scanning: /path/to/your/project

Deleting: /path/to/your/project/node_modules
Deleting: /path/to/your/project/subdir/node_modules

[nmclean] Success: All node_modules removed.
```

## Features

- **Recursive Deletion**: Cleans `node_modules` from the current directory and all subdirectories
- **Safe Operation**: Handles permission errors and missing directories gracefully
- **Colored Output**: Provides clear visual feedback during the cleaning process
- **Fast and Efficient**: Uses Node.js built-in file system operations for optimal performance
- **Zero Dependencies**: Lightweight with no external dependencies

## How It Works

The tool uses Node.js's `fs/promises` API to:
1. Read directory contents recursively
2. Identify directories named `node_modules`
3. Use `fs.rm()` with `recursive: true` and `force: true` to remove them completely
4. Continue scanning even if some deletions fail due to permissions

## Warning

⚠️ **This tool permanently deletes directories and their contents. Make sure you have backups if needed.**

While `node_modules` can always be restored with `npm install`, be cautious when running this in directories containing important data.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Links

- [npm Package](https://www.npmjs.com/package/nmclean)
- [GitHub Repository](https://github.com/mdsiaofficial/nmclean)
- [Issues](https://github.com/mdsiaofficial/nmclean/issues)