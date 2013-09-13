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

Method      |Description
------------|-----------
Sequenceify |Retrives the Amf representation of the encapsulated value.
GetBoolean  |Gets the Boolean if the ValueType of the encapsulated value is Boolean.
GetDouble   |Gets the Double if the ValueType of the encapsulated value is Double.
GetInteger  |Gets the Integer if the ValueType of the encapsulated value is Integer.
GetString   |Gets the String if the ValueType of the encapsulated value is String.
GetReference|Gets the Reference if the ValueType of the encapsulated value is Reference.
GetDate     |Gets the Date if the ValueType of the encapsulated value is Date.
GetObject   |Gets the Object if the ValueType of the encapsulated value is Object.
GetArray    |Gets the Array if the ValueType of the encapsulated value is Array.

### Properties
The **IAmfValue** class has these properties.

Property |Access type|Description
---------|-----------|-----------
ValueType|Read-only  |Gets the type of the encapsulated Amf value. Possible types are defined by AmfValueType.
Value    |Read-only  |Gets the Amf value in the object.

##### Update date: Sep 13, 2013