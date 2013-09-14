# AmfObject class
Represents a AmfObject containing a array of name and **IAmfValue** pairs.

A **AmfObject** inherits the **IAmfObject**, **IAmfValue**, **IMap&lt;IAmfValue&gt;**, **IIterable&lt;IKeyValuePair&lt;String,IAmfValue&gt;&gt;** and IStringable interfaces, which provide methods to iterate through the elements in the array and update its contents. When these are values with duplicated names, the last name/value pair will be stored.

## Syntax

### C＃
public sealed class AmfArray : IAmfArray, IAmfValue, IDictionary&lt;String, IAmfValue&gt;, IEnumerable&lt;KeyValuePair&lt;String, IAmfValue&gt;&gt;, IStringable

### C++
public ref calss AmfArray sealed : public IAmfArray, public IAmfValue, public IMap&lt;String, IAmfValue&gt;, public IIterable&lt;IKeyValuePair&lt;String, IAmfValue&gt;&gt;, public IStringable

### VB
Public NotInheritable Class AmfArray Implements IAmfValue, IDictionary(Of String, IAmfValue), IEnumerable(Of KeyValuePair(Of String, IAmfValue)), IStringable

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

#### IAmfObject

Method           |Description
-----------------|-----------
GetNamedValue 	 |Gets the specified AmfValue object.
SetNamedValue 	 |Sets the value of the first AmfValue object with the specified name to the specified value. If no such object is found, a new name and AmfValue pair is inserted into the AmfValue object.
GetNamedBoolean  |Gets the Boolean value with the specified name, or nullptr if no such named value is found.
GetNamedDouble   |Gets the Double value with the specified name, or nullptr if no such named value is found.
GetNamedInteger  |Gets the Integer value with the specified name, or nullptr if no such named value is found.
GetNamedString   |Gets the String value with the specified name, or nullptr if no such named value is found.
GetNamedReference|Gets the Reference value with the specified name, or nullptr if no such named value is found.
GetNamedDate     |Gets the Date value with the specified name, or nullptr if no such named value is found.
GetNamedObject   |Gets the Object value with the specified name, or nullptr if no such named value is found.
GetNamedArray    |Gets the Array value with the specified name, or nullptr if no such named value is found.

#### IIterable&lt;IKeyValuePair&lt;String, IAmfValue&gt;&gt; [C++]

Method     |Description
-----------|-----------
First [C++]|Returns the iterator for iteration over the key/value pairs in the JsonValue object.

#### IMap&lt;String, IAmfValue&gt; [C++] / IDictionary&lt;String, IAmfValue&gt; [C#, VB]

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

Method  |Description
--------|-----------
Parse   |Parses the specified Amf object into a AmfObject.
TryParse|Parses the specified Amf object into a AmfObject.

### Properties
The **AmfObject** class has these properties.

#### IAmfValue

Property |Access type|Description
---------|-----------|-----------
ValueType|Read-only  |Gets the type of the encapsulated Amf value. Possible types are defined by AmfValueType.
Value    |Read-only  |Gets the Amf value in the object.

#### IMap&lt;String, IAmfValue&gt; [C++] / IDictionary&lt;String, IAmfValue&gt; [C#, VB]

Property           |Access type|Description
-------------------|-----------|-----------
Size [C++]         |Read-only  |Gets the size (count) of the array.
Count [C#, VB]     |Read-only  |Gets the number of elements contained in the collection.
IsReadOnly [C#, VB]|Read-only  |Gets a value indicating whether the collection is read-only.
Item [C#, VB]      |Read/write |Gets or sets the element at the specified index.
Keys [C#, VB]      |Read-only  |Gets an ICollection object containing the keys of the AmfObject.
Values [C#, VB]    |Read-only  |Gets an ICollection object containing the values of the AmfObject.

##### Update date: Sep 14, 2013