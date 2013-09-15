# AmfValue class
Represents a AmfArray containing a array of **IAmfValue**.

A **AmfArray** inherits the **IAmfArray**, **IAmfValue**, **IVector&lt;IAmfValue&gt;**, **IIterable&lt;IAmfValue&gt;**, IStringable interfaces, which provide methods to iterate through the elements in the array and update its contents.

## Syntax

### C＃
public sealed class AmfArray : IAmfArray, IAmfValue, IList&lt;IAmfValue&gt;, IEnumerable&lt;IAmfValue&gt;, IStringable

### C++
public ref calss AmfArray sealed : public IAmfArray, public IAmfValue, public IVector&lt;IAmfValue&gt;, public IIterable&lt;IAmfValue&gt;, public IStringable

### VB
Public NotInheritable Class AmfArray Implements IAmfValue, IList(Of IAmfValue), IEnumerable(Of IAmfValue), IStringable

## Attributes

- **DualApiPartitionAttribute**(NTDDI_WIN8)
- **MarshalingBehaviorAttribute**(Agile)
- **StaticAtribute**(Mntone.Data.Amf.__IAmfArrayStatics, 1u)
- **ThreadingAttribute**(Both)
- **VersionAttribute**(1u)
- **WebHostHiddenAttribute**()

## Members
The **AmfArray** class has these types of members:

- Constructors
- Methods
- Properties

### Constructors
The **AmfArray** class has these constructors.

Constructor|Description
-----------|-----------
AmfArray   |Creates a new AmfArray object that represents a AmfArray.

### Methods
The **AmfArray** class has these methods. It also inherits methods from the **Object** class.

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

#### IAmfArray

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

#### IIterable&lt;IAmfValue&gt; [C++] / IEnumerable&lt;IAmfValue&gt; [C#, VB]

Method                |Description
----------------------|-----------
First [C++]           |Returns the iterator for iteration over the items in the array.
GetEnumerator [C#, VB]|Returns an enumerator that iterates through a collection.

#### IVector&lt;IAmfValue&gt; [C++] / IList&lt;IAmfValue&gt; [C#, VB]

Method           |Description
-----------------|-----------
GetAt [C++]      |Returns the item located at the specified index.
GetView [C++]    |Gets a AmfArray view.
IndexOf [C++]    |Searches for a AmfValue object and returns the zero-based index of its first occurrence within the AmfArray.
IndexOf [C#, VB] |Determines the index of a specific item in the collection.
SetAt [C++]      |Sets the value at the specified index using the provided AmfValue.
InsertAt [C++]   |Inserts a AmfValue into an array at the specified index.
Insert [C#, VB]  |Inserts an item into the collection at the specified index.
RemoveAt [C++]   |Removes the item at the specified index.
RemoveAt [C#, VB]|Removes the element at the specified index of the collection.
Append [C++]     |Adds a new item to the array.
Add [C#, VB]     |Adds a new item to the collection.
Remove [C#, VB]  |Removes the first occurrence of a specific object from the collection.
RemoveAtEnd [C++]|Removes the last item in the array.
Clear            |Removes all items from the array.
Contains [C#, VB]|Determines whether an element is in the collection.
CopyTo [C#, VB]  |Copies the elements of the collection to an array, starting at a particular array index.

#### IStringable

Method  |Description
--------|-----------
ToString|Provides a way to represent the current object as a string. 

#### __IAmfArrayStatics

Method  |Description
--------|-----------
Parse   |Parses the specified Amf array into a AmfArray.
TryParse|Parses the specified Amf array into a AmfArray.

### Properties
The **AmfArray** class has these properties.

#### IAmfValue

Property |Access type|Description
---------|-----------|-----------
ValueType|Read-only  |Gets the type of the encapsulated Amf value. Possible types are defined by AmfValueType.

#### IVector&lt;IAmfValue&gt; [C++] / IList&lt;IAmfValue&gt; [C#, VB]

Property           |Access type|Description
-------------------|-----------|-----------
Size [C++]         |Read-only  |Gets the size (count) of the array.
Count [C#, VB]     |Read-only  |Gets the number of elements contained in the collection.
IsReadOnly [C#, VB]|Read-only  |Gets a value indicating whether the collection is read-only.
Item [C#, VB]      |Read/write |Gets or sets the element at the specified index.

##### Update date: Sep 15, 2013