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

Method           |Description
-----------------|-----------
GetBooleanAt     |Gets the Boolean value at the specified index if the ValueType of the value at that index is Boolean.
GetNumberAt      |Gets the Number value at the specified index if the ValueType of the value at that index is Number.
GetStringAt      |Gets the String value at the specified index if the ValueType of the value at that index is String.
GetDateAt        |Gets the Date value at the specified index if the ValueType of the value at that index is Date.
GetObjectAt      |Gets the ByteArray value at the specified index if the ValueType of the value at that index is Object.
GetVectorIntAt   |Gets the VectorInt value at the specified index if the ValueType of the value at that index is Object.
GetVectorUintAt  |Gets the VectorUint value at the specified index if the ValueType of the value at that index is Object.
GetVectorDoubleAt|Gets the VectorDouble value at the specified index if the ValueType of the value at that index is Object.
GetVectorObjectAt|Gets the VectorObject value at the specified index if the ValueType of the value at that index is Object.
GetObjectAt      |Gets the Object value at the specified index if the ValueType of the value at that index is Object.
GetArrayAt       |Gets the Array value at the specified index if the ValueType of the value at that index is Array.

##### Update date: Nov 15, 2013