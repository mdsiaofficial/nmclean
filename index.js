#!/usr/bin/env node

const fs = require('fs/promises');
const path = require('path');

/**
 * Recursively searches for and deletes node_modules folders
 * @param {string} dir - The directory to start searching from
 */
async function nuke(dir) {
  try {
    const entries = await fs.readdir(dir, { withFileTypes: true });

    for (const entry of entries) {
      const fullPath = path.join(dir, entry.name);

      if (entry.isDirectory()) {
        // Skip hidden directories (dot folders)
        if (entry.name.startsWith('.')) {
          continue;
        }

        if (entry.name === 'node_modules') {
          console.log(`\x1b[31mDeleting:\x1b[0m ${fullPath}`);
          // recursive: true handles the "rm -rf" logic automatically
          await fs.rm(fullPath, { recursive: true, force: true });
        } else {
          // Continue searching subdirectories
          await nuke(fullPath);
        }
      }
    }
  } catch (err) {
    // Handle permission errors or busy files gracefully
    if (err.code === 'EACCES') {
      console.error(`Permission denied: ${dir}`);
    } if (err.code !== 'ENOENT') { // Ignore if folder was already deleted
        console.error(`\x1b[33m[nmclean] Warning:\x1b[0m Could not access ${dir}`);
    } else {
      console.error(`Error processing ${dir}:`, err.message);
    }
  }
}

// Start from current working directory
const targetDir = process.cwd();
console.log(`\x1b[36m--- Node Modules Cleaner (nmclean) ---\x1b[0m`);
console.log(`Scanning: ${targetDir}\n`);

nuke(targetDir).then(() => {
  console.log('\n\x1b[32m[nmclean] Success: All node_modules removed.\x1b[0m');
});
