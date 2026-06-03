#include <iostream>


// ── PART 1: Output Buffering ───────────────────────────────────────────────
//
// Every std::cout call does TWO things:
//   Step 1: Append the data to an output buffer (fast, in RAM)
//   Step 2: Eventually, flush the buffer to the console (slow, I/O)
//
// By default, the buffer is flushed:
//   - When the buffer fills up
//   - When std::cin is called (they're tied together)
//   - When std::endl is used
//   - When the program terminates normally
//
// std::endl does TWO things: outputs '\n' AND flushes the buffer.
// '\n' does ONE thing: outputs a newline character, no flush.
//
// Consequence: using std::endl in a loop = N unnecessary flushes.
// Prefer '\n' unless you explicitly need the flush.

void output_buffering_demo()
{
    // ❌ Flushes buffer 3 times, wasteful in tight loops
    std::cout << "line 1" << std::endl;
    std::cout << "line 2" << std::endl;
    std::cout << "line 3" << std::endl;

    // ✅ Flushes buffer 0 extra times, prefer this
    std::cout << "line 1\n";
    std::cout << "line 2\n";
    std::cout << "line 3\n";

    // Output statements on separate lines don't output newlines automatically.
    // You must explicitly output '\n' to move to the next line.
    std::cout << "no newline here ";
    std::cout << "still on the same line\n";    // \n terminates the line
}


// ── PART 2: Input Buffering ────────────────────────────────────────────────
//
// cin uses the SAME buffering concept as cout.
// Input is stored as: [characters]['\n']
// cin >> x extracts characters and STOPS at the first non-matching character
// or whitespace. The newline '\n' is LEFT in the buffer.
//
// Three extraction scenarios, memorize these:
//
// CASE 1: User types "5\n"
//   cin >> x extracts 5, discards the '\n'. Clean.
//
// CASE 2: User types "5a\n"
//   cin >> x extracts 5, leaves 'a\n' in the buffer.
//   The next cin call reads 'a' without waiting for input.
//   This is the source of most beginner "my input is being skipped" bugs.
//
// CASE 3: User types "b\n" when expecting an int
//   'b' is not a valid integer character, extraction FAILS.
//   x is set to 0 (or left unchanged in older standards).
//   cin enters a FAILED STATE. All subsequent extractions silently do nothing
//   until the stream is explicitly cleared with cin.clear() and flushed
//   with cin.ignore().

void input_buffering_demo()
{
    int x {};

    std::cout << "Enter an integer: ";
    std::cin >> x;    // If input is "42\n", x = 42, '\n' stays in buffer

    // The '\n' left in the buffer matters for getline():
    // std::string line;
    // std::getline(std::cin, line);   // ← would read the leftover '\n' immediately
    //                                 //   solution: cin.ignore() before getline
}


// ── PART 3: Why separate output statements don't create separate lines ─────
//
// This is the #1 beginner confusion with cout.
// cout does NOT add newlines automatically between operator<< calls.
// You are responsible for every character of output, including whitespace.

void newline_responsibility()
{
    std::cout << "Hello";       // outputs: Hello
    std::cout << "World";       // outputs: HelloWorld (no space, no newline!)

    std::cout << "Hello";
    std::cout << '\n';          // NOW it's on its own line
    std::cout << "World";
    std::cout << '\n';
}


int main()
{
    output_buffering_demo();
    input_buffering_demo();
    newline_responsibility();

    return 0;
}
