# AmfValue class
Implements the IAmfValue interface which represents a AmfValue.

A **AmfValue** object can represent the eight primitive Amf value types of Undefined, Null, Boolean, Double, Integer, String, Reference and Date, and can also represent the complex value types of Object and Array by providing ways to access them.

A **AmfValue** object has overloaded constructors to instantiate a new object from a Amf Undefined, Null, Boolean, Double, Integer, String, Reference or Date value and a default constructor that instantiates a **AmfValue** object with a **ValueType** of Null.

## Syntax

### C＃
public sealed class AmfValue : [IAmfValue](Root.IAmfValue.md), IStringable

### C++
public ref calss AmfValue sealed : public [IAmfValue](Root.IAmfValue.md), public IStringable

### VB
Public NotInheritable Class AmfValue Implements [IAmfValue](Root.IAmfValue.md), IStringable

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

#### [IAmfValue](Root.IAmfValue.md)

Method         |Description
---------------|-----------
Sequencify　    |Retrives the Amf representation of the encapsulated value.
GetBoolean     |Gets the Boolean if the ValueType of the encapsulated value is Boolean.
GetNumber      |Gets the Double if the ValueType of the encapsulated value is Number.
GetString      |Gets the String if the ValueType of the encapsulated value is String.
GetDate        |Gets the Date if the ValueType of the encapsulated value is Date.
GetByteArray   |Gets the ByteArray if the ValueType of the encapsulated value is ByteArray.
GetVectorInt   |Gets the VectorInt if the ValueType of the encapsulated value is DVectorIntate.
GetVectorUint  |Gets the VectorUint if the ValueType of the encapsulated value is VectorUint.
GetVectorDouble|Gets the VectorDouble if the ValueType of the encapsulated value is VectorDouble.
GetVectorObject|Gets the VectorObject if the ValueType of the encapsulated value is VectorObject.
GetObject      |Gets the Object if the ValueType of the encapsulated value is Object.
GetArray       |Gets the Array if the ValueType of the encapsulated value is Array.

#### IStringable

Method  |Description
--------|-----------
ToString|Provides a way to represent the current object as a string. 

#### __IAmfValueStatics

Method                 |Description
-----------------------|-----------
CreateUndefinedValue   |Creates a AmfValue.
CreateBooleanValue     |Creates a AmfValue from a Boolean.
CreateNumberValue      |Creates a AmfValue from a Number.
CreateStringValue      |Creates a AmfValue from a String.
CreateDateValue        |Creates a AmfValue from a Date.
CreateXmlValue         |Creates a AmfValue from a Xml.
CreateByteArrayValue   |Creates a AmfValue from a ByteArray.
CreateVectorIntValue   |Creates a AmfValue from a VectorInt.
CreateVectorUintValue  |Creates a AmfValue from a VectorUint.
CreateVectorDoubleValue|Creates a AmfValue from a VectorDouble.
CreateVectorObjectValue|Creates a AmfValue from a VectorObject.
Parse                  |Parses the specified Amf array into a AmfValue.
TryParse               |Parses the specified Amf array into a AmfValue.

### Properties
The **AmfValue** class has these properties.

#### [IAmfValue](Root.IAmfValue.md)

Property |Access type|Description
---------|-----------|-----------
ValueType|Read-only  |Gets the type of the encapsulated Amf value. Possible types are defined by AmfValueType.

##### Update date: Nov 15, 2013