# AmfValue class
Implements the IAmfValue interface which represents a AmfValue.

A **AmfValue** object can represent the eight primitive Amf value types of Undefined, Null, Boolean, Double, Integer, String, Reference and Date, and can also represent the complex value types of Object and Array by providing ways to access them.

A **AmfValue** object has overloaded constructors to instantiate a new object from a Amf Undefined, Null, Boolean, Double, Integer, String, Reference or Date value and a default constructor that instantiates a **AmfValue** object with a **ValueType** of Null.

## Syntax

### C＃
public sealed class AmfValue : IAmfValue, IStringable

### C++
public ref calss AmfValue sealed : public IAmfValue, public IStringable

### VB
Public NotInheritable Class AmfValue Implements IAmfValue, IStringable

## Attributes

- **DualApiPartitionAttribute**(NTDDI_WIN8)
- **MarshalingBehaviorAttribute**(Agile)
- **StaticAtribute**(Mntone.Data.Amf.__IAmfValueStatics, 1u)
- **ThreadingAttribute**(Both)
- **VersionAttribute**(1u)
- **WebHostHiddenAttribute**()

## Members
The **AmfValue** class has these types of members:

- Constructors
- Methods
- Properties

### Constructors
The **AmfValue** class has these constructors.

Constructor|Description
-----------|-----------
AmfValue   |Creates a new AmfValue object that represents a Amf value.

### Methods
The **AmfValue** class has these methods. It also inherits methods from the **Object** class.

#### IAmfValue

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

#### IStringable

Method  |Description
--------|-----------
ToString|Provides a way to represent the current object as a string. 

#### __IAmfValueStatics

Method              |Description
--------------------|-----------
CreateUndefinedValue|Creates a AmfValue.
CreateBooleanValue  |Creates a AmfValue from a Boolean.
CreateDoubleValue   |Creates a AmfValue from a Double.
CreateIntegerValue  |Creates a AmfValue from a Integer.
CreateStringValue   |Creates a AmfValue from a String.
CreateReferenceValue|Creates a AmfValue from a Reference.
CreateDateValue     |Creates a AmfValue from a Date.
CreateXmlValue      |Creates a AmfValue from a Xml.
Parse               |Parses the specified Amf array into a AmfValue.
TryParse            |Parses the specified Amf array into a AmfValue.

### Properties
The **AmfValue** class has these properties.

#### IAmfValue

Property |Access type|Description
---------|-----------|-----------
ValueType|Read-only  |Gets the type of the encapsulated Amf value. Possible types are defined by AmfValueType.

##### Update date: Sep 15, 2013