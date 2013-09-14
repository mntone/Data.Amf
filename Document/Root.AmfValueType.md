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

Member   |Value|Description
---------|-----|-----------
Undefined|0    |The **IAmfValue** object is **Undefined**.
Null     |1    |The **IAmfValue** object is **Null**.
Boolean  |2    |The **IAmfValue** object is **Boolean**.
Double   |3    |The **IAmfValue** object is **Double**.
Integer  |4    |The **IAmfValue** object is **Integer**.
String   |5    |The **IAmfValue** object is **String**.
Reference|6    |The **IAmfValue** object is **Reference**.
Date     |7    |The **IAmfValue** object is **Date**.
Xml      |8    |The **IAmfValue** object is **Xml**.
Object   |9    |The **IAmfValue** object is **Object**.
Array    |10   |The **IAmfValue** object is **Array**.

##### Update date: Sep 14, 2013