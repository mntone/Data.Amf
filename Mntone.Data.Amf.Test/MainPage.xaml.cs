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
			Output( "# Amf0 test" );
			Output( "\n## Parse test" );

			// Number test
			Output( "\n### Number test" );
			Output( "\n[1] 0.0: " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 0, 0, 0, 0, 0, 0, 0, 0, 0 } ).GetDouble().Equals( 0.0 ) ) );
			Output( "\n[2] 0.5: " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 0, 0x3f, 0xe0, 0, 0, 0, 0, 0, 0 } ).GetDouble().Equals( 0.5 ) ) );
			Output( "\n" );
			// ------------

			// Boolean test
			Output( "\n### Boolean test" );
			Output( "\n[1] true: " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 1, 1 } ).GetBoolean().Equals( true ) ) );
			Output( "\n[2] false: " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 1, 0 } ).GetBoolean().Equals( false ) ) );
			Output( "\n" );
			// ------------

			// String test
			Output( "\n### String test" );
			Output( "\n[1] (null): " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 2, 0, 0, 0, 0 } ).GetString().Equals( "" ) ) );
			Output( "\n[2] ASCII: " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 2, 0, 5, 0x41, 0x53, 0x43, 0x49, 0x49 } ).GetString().Equals( "ASCII" ) ) );
			Output( "\n[3] ½: 2B: " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 2, 0, 6, 0xc2, 0xb0, 0x3a, 0x20, 0x32, 0x42 } ).GetString().Equals( "½: 2B" ) ) );
			Output( "\n[4] ⑴: 3B: " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 2, 0, 7, 0xe2, 0x91, 0xb4, 0x3a, 0x20, 0x33, 0x42 } ).GetString().Equals( "⑴: 3B" ) ) );
			Output( "\n// Emoji, Fraction, and so on is not supported!" );
			Output( "\n" );
			// ------------

			// Object test
			Output( "\n### Object test" );
			Output( "\n[1] (null): " + TextOkOrNg( Amf0Parser.Parse( new byte[] { 3, 0, 0, 9 } ).GetObject().GetType().Equals( typeof( AmfObject ) ) ) );
			Output( "\n" );
			// ------------
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
