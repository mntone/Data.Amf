# AmfValueType enumeration
Specifies the Amf object type of a **IAmfValue** object.

## Syntax

### C＃
public enum AmfValueType

### C++
public enum class AmfValueType

### VB
Public Enumeration AmfValueType

## Attributes

- **VersionAttribute**(1u)
- **WebHostHiddenAttribute**()

## Members
The **AmfValueType** enumeration has these members.

Member      |Value|Description
------------|-----|-----------
Undefined   |0    |The **[IAmfValue](Root.IAmfValue.md)** object is **Undefined**.
Null        |1    |The **[IAmfValue](Root.IAmfValue.md)** object is **Null**.
Boolean     |2    |The **[IAmfValue](Root.IAmfValue.md)** object is **Boolean**.
Integer     |3    |The **[IAmfValue](Root.IAmfValue.md)** object is **Integer**.
Double      |4    |The **[IAmfValue](Root.IAmfValue.md)** object is **Double**.
String      |5    |The **[IAmfValue](Root.IAmfValue.md)** object is **String**.
Date        |6    |The **[IAmfValue](Root.IAmfValue.md)** object is **Date**.
Xml         |7    |The **[IAmfValue](Root.IAmfValue.md)** object is **Xml**.
ByteArray   |8    |The **[IAmfValue](Root.IAmfValue.md)** object is **ByteArray**.
VectorInt   |9    |The **[IAmfValue](Root.IAmfValue.md)** object is **VectorInt**.
VectorUint  |10   |The **[IAmfValue](Root.IAmfValue.md)** object is **VectorUint**.
VectorDouble|11   |The **[IAmfValue](Root.IAmfValue.md)** object is **VectorDouble**.
VectorObject|12   |The **[IAmfValue](Root.IAmfValue.md)** object is **VectorObject**.
Object      |13   |The **[IAmfValue](Root.IAmfValue.md)** object is **Object**.
EcmaArray   |14   |The **[IAmfValue](Root.IAmfValue.md)** object is **EcmaArray**.
Array       |15   |The **[IAmfValue](Root.IAmfValue.md)** object is **Array**.
Dictionary  |16   |The **[IAmfValue](Root.IAmfValue.md)** object is **Dictionary**.

##### Update date: Nov 9, 2013