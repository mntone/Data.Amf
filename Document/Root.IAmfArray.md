# IAmfArray interface
Encapsulates a Amf array.

## Syntax

### C＃
public interface IAmfArray

### C++
public interface class IAmfArray

### VB
Public Interface IAmfArray

## Attributes

- **GuidAttribute**("b7396b20-7a54-373b-ac53-6a3123fe642d")
- **VersionAttribute**(1u)
- **WebHostHiddenAttribute**()

## Members
The **IAmfArray** interface has these methods. It also inherits methods from the **Object** class.

Method        |Description
--------------|-----------
GetBooleanAt  |Gets the Boolean value at the specified index if the ValueType of the value at that index is Boolean.
GetDoubleAt   |Gets the Double value at the specified index if the ValueType of the value at that index is Double.
GetIntegerAt  |Gets the Integer value at the specified index if the ValueType of the value at that index is Integer.
GetStringAt   |Gets the String value at the specified index if the ValueType of the value at that index is String.
GetReferenceAt|Gets the Reference value at the specified index if the ValueType of the value at that index is Reference.
GetDateAt     |Gets the Date value at the specified index if the ValueType of the value at that index is Date.
GetObjectAt   |Gets the Object value at the specified index if the ValueType of the value at that index is Object.
GetArrayAt    |Gets the Array value at the specified index if the ValueType of the value at that index is Array.

##### Update date: Sep 13, 2013