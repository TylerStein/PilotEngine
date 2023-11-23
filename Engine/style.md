# Pilot Game Engine Style Guide

- File Names: `snake_case.h`
- Class Names: `class PascalCase {}`
- Private Member Variables: `int mPrivateMember;`
- Public Member Variables: `int publicMember;`
- Method/Function Names: `void flyToTheMoon()`
- Global Variables: `int gGlobalVariable`
- Method/Function Args: `void addValues(int firstValue, int secondValue);`
- Constants: `const int UNCHANGING_VALUE`
- Enum Names/Values: `enum PlayerState { IDLE };`
- Pointer/Refs: `int* ptr; int& ref`
- Bracing: `int main() {\n}`
- Comments/Docs: Doxygen style
- File Structure: `#include` -> directives -> global vars -> class defs -> method defs
- Namespace Name: `namespace Pilot`
- Namespace Use: Avoid `using namespace`
