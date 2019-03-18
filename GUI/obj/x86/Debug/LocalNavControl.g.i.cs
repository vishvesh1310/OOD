﻿#pragma checksum "..\..\..\LocalNavControl.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "729B0BD0E11E6B31E58BF57FADC685EB354EA61C"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using WpfApp1;


namespace WpfApp1 {
    
    
    /// <summary>
    /// LocalNavControl
    /// </summary>
    public partial class LocalNavControl : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 39 "..\..\..\LocalNavControl.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button Refresh;
        
        #line default
        #line hidden
        
        
        #line 44 "..\..\..\LocalNavControl.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock PathTextBlock;
        
        #line default
        #line hidden
        
        
        #line 47 "..\..\..\LocalNavControl.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListBox DirList;
        
        #line default
        #line hidden
        
        
        #line 62 "..\..\..\LocalNavControl.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListBox FileList;
        
        #line default
        #line hidden
        
        
        #line 83 "..\..\..\LocalNavControl.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox txtMsgName;
        
        #line default
        #line hidden
        
        
        #line 85 "..\..\..\LocalNavControl.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox txtMsgDescription;
        
        #line default
        #line hidden
        
        
        #line 87 "..\..\..\LocalNavControl.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox txtMsgCategory;
        
        #line default
        #line hidden
        
        
        #line 89 "..\..\..\LocalNavControl.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox txtMsgPayloadvalue;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/WpfApp1;component/localnavcontrol.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\LocalNavControl.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.Refresh = ((System.Windows.Controls.Button)(target));
            
            #line 39 "..\..\..\LocalNavControl.xaml"
            this.Refresh.Click += new System.Windows.RoutedEventHandler(this.Refresh_Click);
            
            #line default
            #line hidden
            return;
            case 2:
            this.PathTextBlock = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 3:
            this.DirList = ((System.Windows.Controls.ListBox)(target));
            
            #line 47 "..\..\..\LocalNavControl.xaml"
            this.DirList.MouseDoubleClick += new System.Windows.Input.MouseButtonEventHandler(this.DirList_MouseDoubleClick);
            
            #line default
            #line hidden
            return;
            case 4:
            this.FileList = ((System.Windows.Controls.ListBox)(target));
            
            #line 62 "..\..\..\LocalNavControl.xaml"
            this.FileList.MouseDoubleClick += new System.Windows.Input.MouseButtonEventHandler(this.FileList_MouseDoubleClick);
            
            #line default
            #line hidden
            return;
            case 5:
            this.txtMsgName = ((System.Windows.Controls.TextBox)(target));
            return;
            case 6:
            this.txtMsgDescription = ((System.Windows.Controls.TextBox)(target));
            return;
            case 7:
            this.txtMsgCategory = ((System.Windows.Controls.TextBox)(target));
            return;
            case 8:
            this.txtMsgPayloadvalue = ((System.Windows.Controls.TextBox)(target));
            return;
            case 9:
            
            #line 90 "..\..\..\LocalNavControl.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.Cinbutton);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}
