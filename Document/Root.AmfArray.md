# AmfArray class
Represents a AmfArray containing a array of **[IAmfValue](Root.IAmfValue.md)**.

A **AmfArray** inherits the **[IAmfArray](Root.IAmfArray.md)** and **[IAmfValue](Root.IAmfValue.md)**, **IVector&lt;[IAmfValue](Root.IAmfValue.md)&gt;**, **IIterable&lt;[IAmfValue](Root.IAmfValue.md)&gt;**, IStringable interfaces, which provide methods to iterate through the elements in the array and update its contents.

## Syntax

### C＃
public sealed class AmfArray : [IAmfArray](Root.IAmfArray.md), [IAmfValue](Root.IAmfValue.md), IList&lt;[IAmfValue](Root.IAmfValue.md)&gt;, IEnumerable&lt;[IAmfValue](Root.IAmfValue.md)&gt;, IStringable

### C++
public ref calss AmfArray sealed : public [IAmfArray](Root.IAmfArray.md), public [IAmfValue](Root.IAmfValue.md), public IVector&lt;[IAmfValue](Root.IAmfValue.md)&gt;, public IIterable&lt;[IAmfValue](Root.IAmfValue.md)&gt;, public IStringable

### VB
Public NotInheritable Class AmfArray Implements [IAmfArray](Root.IAmfArray.md), [IAmfValue](Root.IAmfValue.md), IList(Of [IAmfValue](Root.IAmfValue.md)), IEnumerable(Of [IAmfValue](Root.IAmfValue.md)), IStringable

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

#### [IAmfArray](Root.IAmfArray.md)

Method           |Description
-----------------|-----------
GetBooleanAt     |Gets the Boolean value at the specified index if the ValueType of the value at that index is Boolean.
GetNumberAt      |Gets the Integer value at the specified index if the ValueType of the value at that index is Number.
GetStringAt      |Gets the String value at the specified index if the ValueType of the value at that index is String.
GetDateAt        |Gets the Date value at the specified index if the ValueType of the value at that index is Date.
GetByteArrayAt   |Gets the ByteArray value at the specified index if the ValueType of the value at that index is ByteArray.
GetVectorIntAt   |Gets the VectorInt value at the specified index if the ValueType of the value at that index is VectorInt.
GetVectorUintAt  |Gets the VectorUint value at the specified index if the ValueType of the value at that index is VectorUint.
GetVectorDoubleAt|Gets the VectorDouble value at the specified index if the ValueType of the value at that index is VectorDouble.
GetVectorObjectAt|Gets the VectorObject value at the specified index if the ValueType of the value at that index is VectorObject.
GetObjectAt      |Gets the Object value at the specified index if the ValueType of the value at that index is Object.
GetArrayAt       |Gets the Array value at the specified index if the ValueType of the value at that index is Array.

#### IIterable&lt;[IAmfValue](Root.IAmfValue.md)&gt; [C++] / IEnumerable&lt;[IAmfValue](Root.IAmfValue.md)&gt; [C#, VB]

Method                |Description
----------------------|-----------
First [C++]           |Returns the iterator for iteration over the items in the array.
GetEnumerator [C#, VB]|Returns an enumerator that iterates through a collection.

#### IVector&lt;[IAmfValue](Root.IAmfValue.md)&gt; [C++] / IList&lt;[IAmfValue](Root.IAmfValue.md)&gt; [C#, VB]

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

#### [IAmfValue](Root.IAmfValue.md)

Property |Access type|Description
---------|-----------|-----------
ValueType|Read-only  |Gets the type of the encapsulated Amf value. Possible types are defined by AmfValueType.

#### IVector&lt;[IAmfValue](Root.IAmfValue.md)&gt; [C++] / IList&lt;[IAmfValue](Root.IAmfValue.md)&gt; [C#, VB]

Property           |Access type|Description
-------------------|-----------|-----------
Size [C++]         |Read-only  |Gets the size (count) of the array.
Count [C#, VB]     |Read-only  |Gets the number of elements contained in the collection.
IsReadOnly [C#, VB]|Read-only  |Gets a value indicating whether the collection is read-only.
Item [C#, VB]      |Read/write |Gets or sets the element at the specified index.

##### Update date: Nov 15, 2013