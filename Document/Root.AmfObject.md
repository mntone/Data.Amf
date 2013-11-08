# AmfObject class
Represents a AmfObject containing a array of name and **[IAmfValue](Root.IAmfValue.md)** pairs.

A **AmfObject** inherits the **[IAmfValue](Root.IAmfValue.md)**, **IMap&lt;[IAmfValue](Root.IAmfValue.md)&gt;**, **IIterable&lt;IKeyValuePair&lt;String,[IAmfValue](Root.IAmfValue.md)&gt;&gt;** and IStringable interfaces, which provide methods to iterate through the elements in the array and update its contents. When these are values with duplicated names, the last name/value pair will be stored.

## Syntax

### C＃
public sealed class AmfObject : [IAmfValue](Root.IAmfValue.md), IDictionary&lt;String, [IAmfValue](Root.IAmfValue.md)&gt;, IEnumerable&lt;KeyValuePair&lt;String, [IAmfValue](Root.IAmfValue.md)&gt;&gt;, IStringable

### C++
public ref calss AmfObject sealed : public public [IAmfValue](Root.IAmfValue.md), public IMap&lt;String, [IAmfValue](Root.IAmfValue.md)&gt;, public IIterable&lt;IKeyValuePair&lt;String, [IAmfValue](Root.IAmfValue.md)&gt;&gt;, public IStringable

### VB
Public NotInheritable Class AmfObject Implements [IAmfValue](Root.IAmfValue.md), IDictionary(Of String, IAmfValue), IEnumerable(Of KeyValuePair(Of String, [IAmfValue](Root.IAmfValue.md))), IStringable

## Attributes

- **DualApiPartitionAttribute**(NTDDI_WIN8)
- **MarshalingBehaviorAttribute**(Agile)
- **StaticAtribute**(Mntone.Data.Amf.__IAmfObjectStatics, 1u)
- **ThreadingAttribute**(Both)
- **VersionAttribute**(1u)
- **WebHostHiddenAttribute**()

## Members
The **AmfObject** class has these types of members:

- Constructors
- Methods
- Properties

### Constructors
The **AmfObject** class has these constructors.

Constructor|Description
-----------|-----------
AmfArray   |Creates a new AmfObject object that represents a AmfObject.

### Methods
The **AmfObject** class has these methods. It also inherits methods from the **Object** class.

#### [IAmfValue](Root.IAmfValue.md)

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

#### __IAmfObjectPublicNonVirtuals

Method              |Description
--------------------|-----------
GetNamedValue       |Gets the specified AmfValue object.
SetNamedValue       |Sets the value of the first AmfValue object with the specified name to the specified value. If no such object is found, a new name and AmfValue pair is inserted into the AmfValue object.
GetNamedBoolean     |Gets the Boolean value with the specified name, or nullptr if no such named value is found.
GetNamedInteger     |Gets the Integer value with the specified name, or nullptr if no such named value is found.
GetNamedDouble      |Gets the Double value with the specified name, or nullptr if no such named value is found.
GetNamedString      |Gets the String value with the specified name, or nullptr if no such named value is found.
GetNamedDate        |Gets the Date value with the specified name, or nullptr if no such named value is found.
GetNamedByteArray   |Gets the ByteArray value with the specified name, or nullptr if no such named value is found.
GetNamedVectorInt   |Gets the VectorInt value with the specified name, or nullptr if no such named value is found.
GetNamedVectorUint  |Gets the VectorUint value with the specified name, or nullptr if no such named value is found.
GetNamedVectorDouble|Gets the VectorDouble value with the specified name, or nullptr if no such named value is found.
GetNamedVectorObject|Gets the VectorObject value with the specified name, or nullptr if no such named value is found.
GetNamedObject      |Gets the Object value with the specified name, or nullptr if no such named value is found.
GetNamedArray       |Gets the Array value with the specified name, or nullptr if no such named value is found.

#### IIterable&lt;IKeyValuePair&lt;String, [IAmfValue](Root.IAmfValue.md)&gt;&gt; [C++], IEnumerator&lt;IKeyValuePair&lt;String, [IAmfValue](Root.IAmfValue.md)&gt;&gt; [C#, VB]

Method                |Description
----------------------|-----------
First [C++]           |Returns the iterator for iteration over the key/value pairs in the JsonObject.
GetEnumerator [C#, VB]|Returns an enumerator that iterates through a collection.

#### IMap&lt;String, [IAmfValue](Root.IAmfValue.md)&gt; [C++] / IDictionary&lt;String, [IAmfValue](Root.IAmfValue.md)&gt; [C#, VB]

Method                       |Description
-----------------------------|-----------
Lookup [C++]                 |Gets the Amf value associated with the supplied key, if an entry with that key exists.
HasKey [C++]                 |Indicates whether the AmfObject has an entry with the requested key.
GetView [C++]                |Gets a AmfObject view.
Insert [C++]                 |Adds a new entry to the AmfObject.
Add(KeyValuePair) [C#, VB]   |Adds a new key-value pair to the AmfObject.
Add(String) [C#, VB]         |Adds an item to the AmfObject.
Remove [C++]                 |Removes the AmfObject associated with the specified key.
Remove(KeyValuePair) [C#, VB]|Removes a specific key-value pair from the AmfObject.
Remove(String) [C#, VB]      |Removes a specific item from the AmfObject.
Clear                        |Removes all items from the array.
Contains [C#, VB]            |Returns a value that indicates whether a specified key-value pair exists in the AmfObject.
ContainsKey [C#, VB]         |Returns a value that indicates whether a specified key exists in the AmfObject.
CopyTo [C#, VB]              |Copies the elements of the collection to an array, starting at a particular array index.
TryGetValue [C#, VB]         |Returns a value that indicates whether a specified key exists in the AmfObject. If an item with that key exists, the item is retrieved as an out parameter.

#### IStringable

Method  |Description
--------|-----------
ToString|Provides a way to represent the current object as a string. 

#### __IAmfObjectStatics

Method         |Description
---------------|-----------
CreateEcmaArray|Creates a AmfObject from a EcmaArray.
Parse          |Parses the specified Amf object into a AmfObject.
TryParse       |Parses the specified Amf object into a AmfObject.

### Properties
The **AmfObject** class has these properties.

#### [IAmfValue](Root.IAmfValue.md)

Property |Access type|Description
---------|-----------|-----------
ValueType|Read-only  |Gets the type of the encapsulated Amf value. Possible types are defined by AmfValueType.

#### __IAmfObjectStatics

Property      |Access type|Description
--------------|-----------|-----------
ClassName     |Read/write |Gets class name.
Externalizable|Read/write |Indicates externalizable object.

#### IMap&lt;String, [IAmfValue](Root.IAmfValue.md)&gt; [C++] / IDictionary&lt;String, [IAmfValue](Root.IAmfValue.md)&gt; [C#, VB]

Property           |Access type|Description
-------------------|-----------|-----------
Size [C++]         |Read-only  |Gets the size (count) of the array.
Count [C#, VB]     |Read-only  |Gets the number of elements contained in the collection.
IsReadOnly [C#, VB]|Read-only  |Gets a value indicating whether the collection is read-only.
Item [C#, VB]      |Read/write |Gets or sets the element at the specified index.
Keys [C#, VB]      |Read-only  |Gets an ICollection object containing the keys of the AmfObject.
Values [C#, VB]    |Read-only  |Gets an ICollection object containing the values of the AmfObject.

##### Update date: Nov 9, 2013