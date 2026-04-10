\# MP3 Tag Editor



\## Overview

A C-based MP3 tag reader and editor that parses ID3v2.3 

format to view and modify metadata in MP3 files.



\## Features

\- View MP3 tags — Title, Artist, Album, Year, Content, Comments

\- Edit any tag field

\- Supports ID3v2.3 format

\- Rewrites MP3 file with updated frame data



\## Files

| File | Description |

|------|-------------|

| `mp3\_header.h` | Function declarations for view and edit |

| `mp3\_view.c` | ID3v2 tag reading and display |

| `mp3\_edit.c` | MP3 tag editing with frame rewrite |

| `main.c` | Entry point with argument parsing and usage guide |



\## Compilation

```bash

gcc main.c mp3\_view.c mp3\_edit.c -o mp3editor

```



\## Usage

```bash

\# View tags

./mp3editor -v sample.mp3



\# Edit tags

./mp3editor -e -a sample.mp3    # Edit Artist

./mp3editor -e -t sample.mp3    # Edit Title

./mp3editor -e -A sample.mp3    # Edit Album

```



\## Tech Stack

\- Language: C

\- Format: ID3v2.3 MP3

\- Concepts: Binary File I/O, Frame parsing, Bit manipulation



