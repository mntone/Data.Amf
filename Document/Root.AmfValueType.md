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
Number      |3    |The **[IAmfValue](Root.IAmfValue.md)** object is **Number**.
String      |4    |The **[IAmfValue](Root.IAmfValue.md)** object is **String**.
Date        |5    |The **[IAmfValue](Root.IAmfValue.md)** object is **Date**.
Xml         |6    |The **[IAmfValue](Root.IAmfValue.md)** object is **Xml**.
ByteArray   |7    |The **[IAmfValue](Root.IAmfValue.md)** object is **ByteArray**.
VectorInt   |8    |The **[IAmfValue](Root.IAmfValue.md)** object is **VectorInt**.
VectorUint  |9    |The **[IAmfValue](Root.IAmfValue.md)** object is **VectorUint**.
VectorDouble|10   |The **[IAmfValue](Root.IAmfValue.md)** object is **VectorDouble**.
VectorObject|11   |The **[IAmfValue](Root.IAmfValue.md)** object is **VectorObject**.
Object      |12   |The **[IAmfValue](Root.IAmfValue.md)** object is **Object**.
EcmaArray   |13   |The **[IAmfValue](Root.IAmfValue.md)** object is **EcmaArray**.
Array       |14   |The **[IAmfValue](Root.IAmfValue.md)** object is **Array**.
Dictionary  |15   |The **[IAmfValue](Root.IAmfValue.md)** object is **Dictionary**.

##### Update date: Nov 15, 2013