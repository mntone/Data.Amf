# IAmfValue interface
Encapsulates a Amf value.

## Syntax

### C＃
public interface IAmfValue

### C++
public interface class IAmfValue

### VB
Public Interface IAmfValue

## Attributes

- **GuidAttribute**("8b21642d-b003-3889-8318-ea7fcaf8dc3f")
- **VersionAttribute**(1u)
- **WebHostHiddenAttribute**()

## Members
The **IAmfValue** interface has these types of members:

- Methods
- Properties

### Methods
The **IAmfValue** interface has these methods. It also inherits methods from the **Object** class.

Method         |Description
---------------|-----------
Sequencify　    |Retrives the Amf representation of the encapsulated value.
GetBoolean     |Gets the Boolean if the ValueType of the encapsulated value is Boolean.
GetInteger     |Gets the Integer if the ValueType of the encapsulated value is Integer.
GetDouble      |Gets the Double if the ValueType of the encapsulated value is Double.
GetString      |Gets the String if the ValueType of the encapsulated value is String.
GetDate        |Gets the Date if the ValueType of the encapsulated value is Date.
GetByteArray   |Gets the ByteArray if the ValueType of the encapsulated value is ByteArray.
GetVectorInt   |Gets the VectorInt if the ValueType of the encapsulated value is DVectorIntate.
GetVectorUint  |Gets the VectorUint if the ValueType of the encapsulated value is VectorUint.
GetVectorDouble|Gets the VectorDouble if the ValueType of the encapsulated value is VectorDouble.
GetVectorObject|Gets the VectorObject if the ValueType of the encapsulated value is VectorObject.
GetObject      |Gets the Object if the ValueType of the encapsulated value is Object.
GetArray       |Gets the Array if the ValueType of the encapsulated value is Array.

### Properties
The **IAmfValue** class has these properties.

Property |Access type|Description
---------|-----------|-----------
ValueType|Read-only  |Gets the type of the encapsulated Amf value. Possible types are defined by AmfValueType.

##### Update date: Nov 9, 2013