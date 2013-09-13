# IAmfObject interface
Encapsulates a Amf object.

## Syntax

### C＃
public interface IAmfObject

### C++
public interface class IAmfObject

### VB
Public Interface IAmfObject

## Attributes

- **GuidAttribute**("92185634-d315-31e0-b470-04adcff85ea3")
- **VersionAttribute**(1u)
- **WebHostHiddenAttribute**()

## Members
The **IAmfObject** interface has these methods. It also inherits methods from the **Object** class.

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

##### Update date: Sep 13, 2013