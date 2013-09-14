using System;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace Mntone.Data.Amf.Test
{
	public sealed partial class MainPage: Page
	{
		public MainPage()
		{
			this.InitializeComponent();
		}

		private void PageLoaded( object sender, RoutedEventArgs e )
		{
			Task.Factory.StartNew( () => Start() );
		}

		private void Start()
		{
			// [Amf0] 
			Output( "# Amf0 test\n" );
			Output( "\n" );
			// ------------

			// Number test
			Output( "## Number test\n" );
			TestAmf0( "[1] 0.0: ", new byte[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, v => v.GetDouble().Equals( 0.0 ) );
			TestAmf0( "[2] 0.5: ", new byte[] { 0, 0x3f, 0xe0, 0, 0, 0, 0, 0, 0 }, f => f.GetDouble().Equals( 0.5 ) );
			Output( "\n" );
			// ------------

			// Boolean test
			Output( "## Boolean test\n" );
			TestAmf0( "[1] true: ", new byte[] { 1, 1 }, f => f.GetBoolean().Equals( true ) );
			TestAmf0( "[2] false: ", new byte[] { 1, 0 }, f => f.GetBoolean().Equals( false ) );
			Output( "\n" );
			// ------------

			// String test
			Output( "## String test\n" );
			TestAmf0( "[1] (null): ", new byte[] { 2, 0, 0, 0, 0 }, f => f.GetString().Equals( "" ) );
			TestAmf0( "[2] ASCII: ", new byte[] { 2, 0, 5, 0x41, 0x53, 0x43, 0x49, 0x49 }, f => f.GetString().Equals( "ASCII" ) );
			TestAmf0( "[3] ½: 2B: ", new byte[] { 2, 0, 6, 0xc2, 0xb0, 0x3a, 0x20, 0x32, 0x42 }, f => f.GetString().Equals( "½: 2B" ) );
			TestAmf0( "[4] ⑴: 3B: ", new byte[] { 2, 0, 7, 0xe2, 0x91, 0xb4, 0x3a, 0x20, 0x33, 0x42 }, f => f.GetString().Equals( "⑴: 3B" ) );
			Output( "// Emoji, Fraction, and so on is not supported!\n" );
			Output( "\n" );
			// ------------

			// Object test
			Output( "## Object test\n" );
			TestAmf0( "[1] {null}: ", new byte[] { 3, 0, 0, 9 }, f => f.ValueType == AmfValueType.Object );
			TestAmf0( "[2] {B: String null}: ", new byte[] { 3, 0, 1, 0x42, 2, 0, 0, 0, 0, 0, 0, 9 }, f => f.GetObject().GetNamedString( "B" ).Equals( "" ) );
			Output( "\n" );
			// ------------

			// Null test
			Output( "## Null test\n" );
			TestAmf0( "[1] null: ", new byte[] { 5 }, f => f.ValueType == AmfValueType.Null );
			Output( "\n" );
			// ------------

			// Undefined test
			Output( "## Undefined test\n" );
			TestAmf0( "[1] undefined: ", new byte[] { 6 }, f => f.ValueType == AmfValueType.Undefined );
			Output( "\n" );
			// ------------

			// Reference test
			Output( "## Reference test\n" );
			TestAmf0( "[1] 0: ", new byte[] { 7, 0, 0 }, f => f.GetReference().Equals( 0 ) );
			TestAmf0( "[2] 4369: ", new byte[] { 7, 0x11, 0x11 }, f => f.GetReference().Equals( 4369 ) );
			Output( "\n" );
			// ------------

			// EcmaArray test
			Output( "## EcmaArray test\n" );
			TestAmf0( "[1] {null}: ", new byte[] { 8, 0, 0, 0, 0, 0, 0, 9 }, f => f.ValueType == AmfValueType.Object );
			TestAmf0( "[2] {B: String null}: ", new byte[] { 8, 0, 0, 0, 1, 0, 1, 0x42, 2, 0, 0, 0, 0, 0, 0, 9 }, f => f.GetObject().GetNamedString( "B" ).Equals( "" ) );
			Output( "\n" );
			// ------------

			// StrictArray test
			Output( "## StrictArray test\n" );
			TestAmf0( "[1] [null]: ", new byte[] { 10, 0, 0, 0, 0 }, f => f.ValueType == AmfValueType.Array );
			TestAmf0( "[2] [0, true]: ", new byte[] { 10, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }, f => f.GetArray()[0].GetDouble() == 0.0 && f.GetArray()[1].GetBoolean() );
			Output( "\n" );
			// ------------

			// Date test
			Output( "## Date test\n" );
			TestAmf0( "[1] [2013/10/13]: ", new byte[] { 11, 0x42, 0x74, 0x1a, 0xd2, 0xe6, 0x18, 0x00, 0x00, 0, 0 }, f => f.GetDate().Year == 2013 && f.GetDate().Month == 10 && f.GetDate().Day == 13 );
			Output( "\n" );
			// ------------

			// LongString test
			Output( "## LongString test\n" );
			var ls = new byte[5 + 0x10000];
			ls[0] = 12; ls[1] = 0; ls[2] = 1; ls[3] = 0; ls[4] = 0;
			var testLs = new StringBuilder();
			for( var i = 0; i < 0x4000; ++i )
			{
				ls[5 + 4 * i] = 0x71; ls[5 + 4 * i + 1] = 0x72; ls[5 + 4 * i + 2] = 0x73; ls[5 + 4 * i + 3] = 0x74;
				testLs.Append( "qrst" );
			}
			TestAmf0( "[1] qrst x 0x4000: ", ls, f => f.GetString() == testLs.ToString() );
			Output( "\n" );
			// ------------

			// XmlDocument test
			Output( "## XmlDocument test\n" );
			TestAmf0( "[1] <root>: ", new byte[] { 0x0f, 0, 0, 0, 6, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, f => f.GetString().Equals( "<root>" ) );
			Output( "\n" );
			// ------------

			// TypedObject test
			Output( "## TypedObject test\n" );
			TestAmf0( "[1] Test: {null}: ", new byte[] { 0x10, 0, 4, 0x54, 0x65, 0x73, 0x74, 0, 0, 9 }, f => f.ValueType == AmfValueType.Object && f.GetObject().ClassName == "Test" );
			Output( "\n" );
			// ------------

			Output( "\n" );

			// [Class] 
			Output( "# Class test\n" );
			Output( "These tests check casting object (IAmfValue^ to Amf～).\n" );
			Output( "\n" );
			// ------------

			// From value Parse test
			Output( "# From value Parse test\n" );
			Output( "[1] Double 0: " + TextOkOrNg( AmfValue.Parse( new byte[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType.Amf0 ).GetDouble().Equals( 0.0 ) ) + '\n' );
			Output( "[2] Object null: " + TextOkOrNg( AmfValue.Parse( new byte[] { 3, 0, 0, 9 }, AmfEncodingType.Amf0 ).GetObject().Count == 0 ) + '\n' );
			Output( "[3] Array null: " + TextOkOrNg( AmfValue.Parse( new byte[] { 10, 0, 0, 0, 0 }, AmfEncodingType.Amf0 ).GetArray().Count == 0 ) + '\n' );
			Output( "\n" );
			// ------------

			// From object Parse test
			Output( "# From object Parse test\n" );
			Output( "[1] Double 0: " + TextOkOrNg( AmfObject.Parse( new byte[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType.Amf0 ).GetDouble().Equals( 0.0 ) ) + '\n' );
			Output( "[2] Object null: " + TextOkOrNg( AmfObject.Parse( new byte[] { 3, 0, 0, 9 }, AmfEncodingType.Amf0 ).Count == 0 ) + '\n' );
			Output( "[3] Array null: " + TextOkOrNg( AmfObject.Parse( new byte[] { 10, 0, 0, 0, 0 }, AmfEncodingType.Amf0 ).GetArray().Count == 0 ) + '\n' );
			Output( "\n" );
			// ------------

			// From array Parse test
			Output( "# From array Parse test\n" );
			Output( "[1] Double 0: " + TextOkOrNg( AmfArray.Parse( new byte[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType.Amf0 ).GetDouble().Equals( 0.0 ) ) + '\n' );
			Output( "[2] Object null: " + TextOkOrNg( AmfArray.Parse( new byte[] { 3, 0, 0, 9 }, AmfEncodingType.Amf0 ).GetObject().Count == 0 ) + '\n' );
			Output( "[3] Array null: " + TextOkOrNg( AmfArray.Parse( new byte[] { 10, 0, 0, 0, 0 }, AmfEncodingType.Amf0 ).Count == 0 ) + '\n' );
			Output( "\n" );
			// ------------


			// From value TryParse test
			Output( "# From value TryParse test\n" );
			AmfValue bufValue;
			Output( "[1] Double 0: " + TextOkOrNg( AmfValue.TryParse( new byte[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType.Amf0, out bufValue ) && bufValue.GetDouble().Equals( 0.0 ) ) + '\n' );
			Output( "[2] Object null: " + TextOkOrNg( AmfValue.TryParse( new byte[] { 3, 0, 0, 9 }, AmfEncodingType.Amf0, out bufValue ) && bufValue.GetObject().Count == 0 ) + '\n' );
			Output( "[3] Array null: " + TextOkOrNg( AmfValue.TryParse( new byte[] { 10, 0, 0, 0, 0 }, AmfEncodingType.Amf0, out bufValue ) && bufValue.GetArray().Count == 0 ) + '\n' );
			Output( "\n" );
			// ------------

			// From object TryParse test
			Output( "# From object TryParse test\n" );
			AmfObject bufObject;
			Output( "[1] Double 0: " + TextOkOrNg( AmfObject.TryParse( new byte[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType.Amf0, out bufObject ) && bufObject.GetDouble().Equals( 0.0 ) ) + '\n' );
			Output( "[2] Object null: " + TextOkOrNg( AmfObject.TryParse( new byte[] { 3, 0, 0, 9 }, AmfEncodingType.Amf0, out bufObject ) && bufObject.Count == 0 ) + '\n' );
			Output( "[3] Array null: " + TextOkOrNg( AmfObject.TryParse( new byte[] { 10, 0, 0, 0, 0 }, AmfEncodingType.Amf0, out bufObject ) && bufObject.GetArray().Count == 0 ) + '\n' );
			Output( "\n" );
			// ------------

			// From array TryParse test
			Output( "# From array TryParse test\n" );
			AmfArray bufArray;
			Output( "[1] Double 0: " + TextOkOrNg( AmfArray.TryParse( new byte[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType.Amf0, out bufArray ) && bufArray.GetDouble().Equals( 0.0 ) ) + '\n' );
			Output( "[2] Object null: " + TextOkOrNg( AmfArray.TryParse( new byte[] { 3, 0, 0, 9 }, AmfEncodingType.Amf0, out bufArray ) && bufArray.GetObject().Count == 0 ) + '\n' );
			Output( "[3] Array null: " + TextOkOrNg( AmfArray.TryParse( new byte[] { 10, 0, 0, 0, 0 }, AmfEncodingType.Amf0, out bufArray ) && bufArray.Count == 0 ) + '\n' );
			Output( "\n" );
			// ------------

			Output( "\n" );

			// [Master] 
			Output( "# Master test\n" );
			Output( "These tests check with real data.\n" );
			TestAmf0( "[1] Rtmp command data: ", new byte[] { 10, 0, 0, 0, 4, 0x02, 0x00, 0x07, 0x5f, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x66, 0x6d, 0x73, 0x56, 0x65, 0x72, 0x02, 0x00, 0x0d, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x00, 0x0c, 0x63, 0x61, 0x70, 0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x00, 0x40, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0x00, 0x05, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x02, 0x00, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65, 0x02, 0x00, 0x1d, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0x00, 0x0b, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x02, 0x00, 0x14, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64, 0x65, 0x64, 0x00, 0x0e, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09 }, f => f.ValueType == AmfValueType.Array );
			Output( "\n" );
			// ------------
		}

		private void TestAmf0( string start, byte[] rawData, Func<IAmfValue, bool> readCheck )
		{
			var sb = new StringBuilder( start );
			var r = Amf0Parser.Parse( rawData );
			var st = r.ToString();
			sb.Append( TextOkOrNg( readCheck( r ) ) ); // Parser check
			//sb.Append( ", " );
			//sb.Append( TextOkOrNg( ArrayEquals(rawData, )) // Sequencer check
			Output( sb.ToString() + '\n' );
		}

		private string TextOkOrNg( bool flag )
		{
			return flag ? "OK" : "NG";
		}

		private bool ArrayEquals( byte[] a, byte[] b )
		{
			if( a.Length != b.Length )
				return false;
			for( int i = 0; i < a.Length; i++ )
			{
				if( !a.GetValue( i ).Equals( b.GetValue( i ) ) )
				{
					return false;
				}
			}
			return true;
		}

		private void Output( string text )
		{
			Dispatcher.RunAsync( Windows.UI.Core.CoreDispatcherPriority.High, () => textBox.Text += text );
		}
	}
}
