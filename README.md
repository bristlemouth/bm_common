# Bristlemouth Common

Under construction as of September 2024!

If you're not sure whether you're in the right place, check out
https://github.com/bristlemouth/bm_protocol

The Bristlemouth core development team is working to increase the
accessibility of Bristlemouth firmware, especially for potential
integrators of hardware that would enhance the ecosystem.

## Constraints

We're just getting started, but here are some of our intentions.

In order to enable future python and rust bindings, Bristlemouth code should be
written in pure, strict C. Our starting intent is to use the C17 standard.
This is a guideline, not a hard-and-fast rule. When a component could benefit
from C++ features, there should be a public discussion about the pros and cons.

The code in this library should never unexpectedly halt the application.
Instead we should return error codes that clients must handle.

We may include a generic assert macro that clients can define as appropriate,
for example as a no-op or to gather coredump info.

CMake should just work, with as few arguments as possible.

## Code Style

- File names should be `snake_case`.
- Types should use `UpperCamelCase`. Avoid suffixes like `_t`.
- Enum variants should also use `UpperCamelCase`.
- Functions should use `snake_case`.
- Local variables should use `snake_case`.
- Statics and constants should use `SCREAMING_SNAKE_CASE`.
- When a component has one-time setup code and then a function to repeatedly run, the names should be `init` and `update`.
- Formatting and whitespace should follow clang-format.
- If there's a question, let's take inspiration from the [Rust API Guidelines](https://rust-lang.github.io/api-guidelines/naming.html).


Other elements that integrators may need to specify:

- The path to `bm_common` source code for the build.
- The versions of different components to ensure compatible communication on the Bristlemouth network.
- Configuration keys and value types in the hardware, system, and user partitions.
- Resource interests, including topics that are published or subscribed to, and services that are hosted (giving replies) or to which requests are made.

More to come...
