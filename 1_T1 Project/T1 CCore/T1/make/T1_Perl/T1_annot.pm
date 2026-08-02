######################################################################################
#
#   File:           T1_annot.pm
#
#   Description:    Generate T1 config datastructures
#
#   $Author: jialinli $
#
#   $Revision: 370 $
#
#   Copyright:      GLIWA embedded systems GmbH & Co. KG
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################

use 5.006_000;

package T1_annot;
require Exporter;
our @ISA = ("Exporter");
our @EXPORT = qw(
    GenT1Annotations
);

use strict;
use warnings;

use constant DEBUG => 0;    # Change to 1 to enable debug logging information

######################################################################################
# Sub routine to generate T1.stack known-memory/indirect annotations
######################################################################################
sub GenT1Annotations($$$)
{
    my $configRef = shift;
    my $fh = shift;
    my $fhPCRef = shift;
    my %config = %$configRef;
    my @fhPC = @$fhPCRef;
    my $nonRemote = 'false';
    my $remote = 'false';
    foreach my $coreId (0..$config{'nOfCores'} - 1)
    {
        if( exists $config{'contRunsOnCore'}{$coreId} )
        {
            if( $config{'contRunsOnCore'}{$coreId} == $coreId )
            {
                $nonRemote = 'true';
            }
            else
            {
                $remote = 'true';
            }
        }
        else
        {
            $nonRemote = 'true';
        }
    }

    print $fh <<EOT;
<?xml version="1.0" encoding="utf-8"?>
<!-- mpc5xxx -->
<Annotations>
EOT
    foreach my $coreId (0..$config{'nOfCores'} - 1)
    {
        my $fhCoreX = $fhPC[$coreId];
        print $fhCoreX <<EOT;
<?xml version="1.0" encoding="utf-8"?>
<!-- mpc5xxx -->
<Annotations>
EOT
    }
    ######################################################################################
    # Recustions
    ######################################################################################

    if( $config{'foregroundCont'} eq 'true' )
    {
        foreach my $coreId (0..$config{'nOfCores'} - 1)
        {
            print $fh <<EOT;
<Recursion Function="T1_Dispatch$coreId" Depth="2" Kind="Bounded" Optional="true" />
EOT
        }
        print $fh <<EOT;
<Recursion Function="T1_BrokenInterval" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_LargeInterval" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_NearBrokenInterval" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_NearLargeInterval" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_StartTask" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_StartTaskVS" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_StopFlexSwd" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_StopFlexSwdVS" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_StopFlexSwdSyncIsTraceTimer" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_StopStartTask" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_StopStartTaskVS" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_33680" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_30133" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_TraceUint32RestNoSuspFg" Depth="1" Kind="Bounded" Optional="true" />
<Recursion Function="T1_TraceUint56RestNoSuspFg" Depth="1" Kind="Bounded" Optional="true" />

EOT
    }
    ######################################################################################
    # Indirect annotations
    ######################################################################################

    if( $config{'foregroundCont'} eq 'true' )
    {
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_83340" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_81607" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_27683" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_03006" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_11051" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_33764" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_30582" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_39470" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_70400" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_61772" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_57670" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_12808" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_14607" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_26289" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_21138" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_28624" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_66268" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_16390" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_92395" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_75757" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_06587" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_59059" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_58069" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_70336" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_00560" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_56968" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_56133" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_99385" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_69175" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_15443" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_30476" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_26739" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_77158" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_31127" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_32918" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_95529" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_17038" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_39922" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_17038" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_01087" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_41150" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_40769" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_29290" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_18990" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_67110" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_64715" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_83340" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_81607" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_27683" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_03006" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_11051" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_33764" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_30582" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_39470" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_70400" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_61772" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_57670" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_12808" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_14607" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_26289" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_21138" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_28624" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_66268" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_16390" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_92395" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_75757" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_06587" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_59059" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_58069" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_70336" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_00560" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_56968" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_56133" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_99385" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_69175" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_15443" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_30476" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_26739" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_77158" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_31127" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_32918" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_95529" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_17038" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_39922" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_17038" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_01087" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_41150" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_40769" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_29290" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_18990" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_67110" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_64715" AnnotationSourceType="Manual" Optional="true" />' . "\n";
    }
    else
    {
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_83251" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_98327" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_25463" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_36731" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_56851" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_44485" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_13877" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_64762" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_42629" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_86406" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_03518" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_59087" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_29443" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_69561" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_43197" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_80450" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_17153" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_67647" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_69630" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_30822" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_90042" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_93770" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_31542" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_40087" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_36611" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_64981" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_87135" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_52494" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_88174" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_82275" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_39825" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_64395" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_65991" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_45184" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_66687" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_51748" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_93215" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_19155" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_00899" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_28509" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_33621" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_50711" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_17218" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_36285" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_66760" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_ExceptionHandler" To="T1_13591" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_83251" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_98327" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_25463" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_36731" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_56851" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_44485" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_13877" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_64762" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_42629" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_86406" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_03518" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_59087" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_29443" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_69561" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_43197" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_80450" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_17153" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_67647" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_69630" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_30822" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_90042" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_93770" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_31542" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_40087" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_36611" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_64981" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_87135" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_52494" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_88174" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_82275" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_39825" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_64395" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_65991" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_45184" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_66687" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_51748" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_93215" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_19155" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_00899" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_28509" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_33621" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_50711" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_17218" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_36285" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_66760" AnnotationSourceType="Manual" Optional="true" />' . "\n";
            print $fh '<Indirect FromFunction="T1_22152" To="T1_13591" AnnotationSourceType="Manual" Optional="true" />' . "\n";
    }
    print $fh <<EOT;
<Indirect FromFunction="T1_22339" To="T1_23901" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_22339" To="T1_78128" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_22339" To="T1_24398" AnnotationSourceType="Manual" Optional="true" />
EOT
    if( $config{'foregroundCont'} eq 'true' )
    {
        print $fh <<EOT;
<Indirect FromFunction="T1_22339" To="T1_11056" AnnotationSourceType="Manual" Optional="true" />
EOT
    }
    else
    {
        print $fh <<EOT;
<Indirect FromFunction="T1_22339" To="T1_11338" AnnotationSourceType="Manual" Optional="true" />
EOT
    }
    if( $nonRemote eq 'true' )
    {
        print $fh <<EOT;
<Indirect FromFunction="T1_SetStopTriggerPC" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_48925" To="T1_77011" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_48925" To="T1_64984" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_48925" To="T1_61840" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_ContBgHandlerDirectPC
        print $fh <<EOT;
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_48477" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_29632" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_77011" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_64984" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_61840" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_77917" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_45355" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_36789" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_85149" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_68579" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_69180" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_25756" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_76896" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_17241" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_09782" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_77597" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectPC" To="T1_98957" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_00924
        print $fh <<EOT;
<Indirect FromFunction="T1_00924" To="T1_48477" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_29632" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_77011" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_64984" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_61840" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_77917" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_45355" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_36789" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_85149" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_68579" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_69180" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_25756" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_76896" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_17241" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_09782" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_77597" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_98957" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_75264" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00924" To="T1_03360" AnnotationSourceType="Manual" Optional="true" />
EOT
    }
    if( $remote eq 'true' )
    {
        print $fh <<EOT;
<Indirect FromFunction="T1_SetStopTriggerPC" To="T1_TraceEventNoSuspTimeRC__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_44177" To="T1_77011" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_44177" To="T1_64984" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_44177" To="T1_61840" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_ContBgHandlerDirectRCPC
        print $fh <<EOT;
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_48477" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_29632" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_77011" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_64984" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_61840" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_77917" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_45355" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_36789" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_85149" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_68579" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_69180" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_25756" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_76896" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_17241" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_09782" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_77597" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ContBgHandlerDirectRCPC" To="T1_98957" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_13531
        print $fh <<EOT;
<Indirect FromFunction="T1_13531" To="T1_48477" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_29632" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_77011" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_64984" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_61840" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_77917" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_45355" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_36789" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_85149" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_68579" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_69180" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_25756" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_76896" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_17241" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_09782" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_77597" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_98957" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_75264" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13531" To="T1_03360" AnnotationSourceType="Manual" Optional="true" />
EOT
    }

    # T1_83538
    print $fh <<EOT;
<Indirect FromFunction="T1_83538" To="T1_78128" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_83538" To="T1_24398" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_83538" To="T1_63278" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_83538" To="T1_46829" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_83538" To="T1_23901" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_83538" To="T1_99703" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_DoVStpw8
    print $fh <<EOT;
<Indirect FromFunction="T1_75264" To="T1_48477" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_29632" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_77011" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_64984" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_61840" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_77917" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_45355" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_36789" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_85149" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_68579" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_69180" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_25756" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_76896" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_17241" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_09782" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_77597" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_75264" To="T1_98957" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_TxCompleteNotification
    print $fh <<EOT;
<Indirect FromFunction="T1_TxCompleteNotification" To="T1_34194" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_TxCompleteNotification" To="T1_16531" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_RxBufferRequest
    print $fh <<EOT;
<Indirect FromFunction="T1_RxBufferRequest" To="T1_09922" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_RxBufferRequest" To="T1_94134" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_RxBufferRequest" To="T1_10888" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_RxBufferRequest" To="T1_05834" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_RxBufferRequest" To="T1_55310" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_InitPC
    print $fh <<EOT;
<Indirect FromFunction="T1_InitPC" To="T1_37829" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_InitPC" To="T1_71929" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_InitPC" To="T1_77194" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_InitPC" To="T1_94913" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_InitPC" To="T1_80322" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_InitPC" To="T1_10419" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_HandlerPC
    print $fh <<EOT;
<Indirect FromFunction="T1_HandlerPC" To="T1_59011" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_HandlerPC" To="T1_60208" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_HandlerPC" To="T1_52792" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_HandlerPC" To="T1_82122" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_85482
    print $fh <<EOT;
<Indirect FromFunction="T1_85482" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_85482" To="T1_TraceEventNoSuspTimeRC__" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_TraceData_
    print $fh <<EOT;
<Indirect FromFunction="T1_TraceData_" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_TraceData_" To="T1_TraceEventNoSuspTimeRC__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_TraceDataNoSusp_" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_TraceDataNoSusp_" To="T1_TraceEventNoSuspTimeRC__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_TraceDataNoSuspTime_" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_TraceDataNoSuspTime_" To="T1_TraceEventNoSuspTimeRC__" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_17419
    print $fh <<EOT;
<Indirect FromFunction="T1_17419" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_17419" To="T1_TraceEventNoSuspTimeRC__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_52103" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_OuterTrapCls3HndlrCore, T1_45277, and T1_TraceUint32RestNoSuspFg
    if( $config{'foregroundCont'} eq 'true' )
    {
        foreach my $coreId (0..$config{'nOfCores'} - 1)
        {
            print $fh <<EOT;
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_Empty" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_EmptyVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartStopNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartStopNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartIncStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartIncStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartNoActTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartNoActTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_WaitTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_WaitTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_ResumeTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_ResumeTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartNoActTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartNoActTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartIncFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopStartIncFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartFlexSwd" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StartFlexSwdVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopFlexSwdSyncIsTraceTimer" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopFlexSwd" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_StopFlexSwdVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_ActivateAndTraceTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_ActivateAndTraceTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_ActivateTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Dispatch$coreId" To="T1_ActivateTaskVS" AnnotationSourceType="Manual" Optional="true" />
EOT
        }
        print $fh <<EOT;
<Indirect FromFunction="T1_DispatchTimePC" To="T1_Empty" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_EmptyVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartStopNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartStopNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartIncStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartIncStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartNoActTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartNoActTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_WaitTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_WaitTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_ResumeTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_ResumeTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartNoActTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartNoActTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartIncFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopStartIncFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartFlexSwd" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StartFlexSwdVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopFlexSwdSyncIsTraceTimer" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopFlexSwd" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_StopFlexSwdVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_ActivateAndTraceTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_ActivateAndTraceTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_ActivateTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_DispatchTimePC" To="T1_ActivateTaskVS" AnnotationSourceType="Manual" Optional="true" />
EOT
        print $fh <<EOT;
<Indirect FromFunction="T1_BrokenInterval" To="T1_Empty" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_EmptyVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartStopNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartStopNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartIncStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartIncStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartNoActTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartNoActTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_WaitTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_WaitTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_ResumeTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_ResumeTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartNoActTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartNoActTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartIncFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopStartIncFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartFlexSwd" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StartFlexSwdVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopFlexSwdSyncIsTraceTimer" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopFlexSwd" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_StopFlexSwdVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_ActivateAndTraceTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_ActivateAndTraceTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_ActivateTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_BrokenInterval" To="T1_ActivateTaskVS" AnnotationSourceType="Manual" Optional="true" />
EOT
        print $fh <<EOT;
<Indirect FromFunction="T1_LargeInterval" To="T1_Empty" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_EmptyVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartStopNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartStopNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartNoIptTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartNoIptTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartIncStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartIncStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartNoActTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartNoActTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_WaitTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_WaitTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_ResumeTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_ResumeTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartNoActTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartNoActTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartIncFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopStartIncFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartFlexSwd" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StartFlexSwdVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopFlexStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopFlexStopwatchVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopFlexSwdSyncIsTraceTimer" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopFlexSwd" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_StopFlexSwdVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_ActivateAndTraceTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_ActivateAndTraceTaskVS" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_ActivateTask" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_LargeInterval" To="T1_ActivateTaskVS" AnnotationSourceType="Manual" Optional="true" />
EOT
        print $fh <<EOT;
<Indirect FromFunction="T1_ActivateTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ActivateTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ActivateAndTraceTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ActivateAndTraceTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_EmptyVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_EmptyVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ResumeTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ResumeTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartFlexStopwatchVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartFlexStopwatchVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartFlexSwdVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartFlexSwdVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartNoActTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartNoActTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartStopNoIptTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartStopNoIptTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartStopwatchVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartStopwatchVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopFlexStopwatchVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopFlexStopwatchVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopFlexSwdVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopFlexSwdVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartIncFlexStopwatchVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartIncFlexStopwatchVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartIncStopwatchVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartIncStopwatchVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartNoActTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartNoActTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartStopwatchVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartStopwatchVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartNoIptTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartNoIptTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStopwatchVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStopwatchVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_30133" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_30133" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartNoIptTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartNoIptTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_WaitTaskVS" To="T1_FgDoVStpw8" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_WaitTaskVS" To="T1_FgDoVStpw64" AnnotationSourceType="Manual" Optional="true" />

<Indirect FromFunction="T1_TraceEventNoSusp__" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_TraceUint32RestNoSuspFg" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_TraceUint56RestNoSuspFg" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_00560" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_87483" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_01087" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_65984" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_03006" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_89772" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_06587" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_17412" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_11056" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_15112" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_14607" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_09037" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_15443" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_77308" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_17038" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_71060" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_21138" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_48615" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_26289" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_73317" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_26739" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_91709" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_27683" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_97033" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_28624" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_04754" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_29290" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_22136" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_30476" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_11724" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_39922" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_82644" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_40769" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_90751" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_41150" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_84065" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_45277" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_45277" To="T1_TraceUint32RestNoSuspFg" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_55605" To="T1_TraceUint32RestNoSuspFg" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_50960" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_98433" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_57670" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_81611" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_58069" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_37494" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_64715" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_64715" To="T1_TraceUint32RestNoSuspFg" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_70273" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_11526" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_77158" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_48633" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_95122" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_92380" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_62219" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_10151" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_21454" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_54865" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_97350" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_48162" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_96783" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_03678" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />

<Indirect FromFunction="T1_FgDoVStpw8" To="T1_83280" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_42377" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_17200" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_18384" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_89107" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_62523" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_60609" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_62523" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_60609" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_62523" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_60609" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_62523" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_60609" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_62523" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_60609" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_62523" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_60609" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_62523" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_60609" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_62523" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_60609" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_56817" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_70637" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_88415" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_95453" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_63683" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_13443" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_02655" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_32373" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_24237" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_FgDoVStpw8" To="T1_49629" AnnotationSourceType="Manual" Optional="true" />

<Indirect FromFunction="T1_21725" To="T1_StartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_21725" To="T1_StopStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_21725" To="T1_StopStartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_99183" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_30130" To="T1_StartStopwatch" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_30130" To="T1_StopStopwatch" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_ContResetInternal
        print $fh <<EOT;
<Indirect FromFunction="T1_34149" To="T1_97784" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_28386" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_13399" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_09191" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_97862" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_39580" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_33337" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1.stack memory analyser is supposed to resolve this without annotations. But it does not work for RH850
        # T1_ConfigEventChainPC
        print $fh <<EOT;
<Indirect FromFunction="T1_ConfigEventChainPC" To="T1_93894" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_ScopeOverheadSequenceNoSuspPC
        print $fh <<EOT;
<Indirect FromFunction="T1_ScopeOverheadSequenceNoSuspPC" To="T1_73873" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ScopeOverheadSequenceNoSuspPC" To="T1_21725" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ScopeOverheadSequenceNoSuspPC" To="T1_30130" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_37426
        print $fh <<EOT;
<Indirect FromFunction="T1_37426" To="T1_28386" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_37426" To="T1_39580" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_37539
        print $fh <<EOT;
<Indirect FromFunction="T1_37539" To="T1_97862" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_49569
        print $fh <<EOT;
<Indirect FromFunction="T1_49569" To="T1_28386" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_59506
        print $fh <<EOT;
<Indirect FromFunction="T1_59506" To="T1_33337" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59506" To="T1_97784" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_68569
        print $fh <<EOT;
<Indirect FromFunction="T1_68569" To="T1_15052" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_27017" To="T1_15052" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_71929
        print $fh <<EOT;
<Indirect FromFunction="T1_71929" To="T1_18442" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_75433
        print $fh <<EOT;
<Indirect FromFunction="T1_75433" To="T1_28386" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_83285
        print $fh <<EOT;
<Indirect FromFunction="T1_83285" To="T1_29820" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_59011
        print $fh <<EOT;
<Indirect FromFunction="T1_59011" To="T1_13357" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59011" To="T1_88207" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59011" To="T1_25240" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59011" To="T1_28386" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59011" To="T1_55266" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_75917
        print $fh <<EOT;
<Indirect FromFunction="T1_75917" To="T1_13357" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_93023
        print $fh <<EOT;
<Indirect FromFunction="T1_93023" To="T1_28386" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_93930
        print $fh <<EOT;
<Indirect FromFunction="T1_93930" To="T1_78597" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_94799
        print $fh <<EOT;
<Indirect FromFunction="T1_94799" To="T1_55266" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_97036
        print $fh <<EOT;
<Indirect FromFunction="T1_97036" To="T1_93894" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_94134
        print $fh <<EOT;
<Indirect FromFunction="T1_94134" To="T1_55266" AnnotationSourceType="Manual" Optional="true" />
EOT
        # Functions which call T1_DispatchX
        print $fh <<EOT;
<Indirect FromFunction="T1_75057" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_65857" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_74926
        print $fh <<EOT;
<Indirect FromFunction="T1_96783" To="T1_TraceUint32RestNoSuspFg" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_03678" To="T1_TraceUint32RestNoSuspFg" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_56851
        print $fh <<EOT;
<Indirect FromFunction="T1_11051" To="T1_15052" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_33925" To="T1_40585" AnnotationSourceType="Manual" Optional="true" />
EOT

        # For ARM7M FPBV1
        # Functions which call T1_DispatchX
        print $fh <<EOT;
<Indirect FromFunction="T1_10631" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_15771" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_21329" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_22866" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_23768" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34018" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_42056" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_53337" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_54521" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59806" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_68481" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_69247" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_85686" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_96827" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_96995" To="T1_Dispatch0" AnnotationSourceType="Manual" Optional="true" />
EOT

        # For MPC5xxx
        # Functions which call T1_TraceEventNoSuspTime__
        print $fh <<EOT;
<Indirect FromFunction="T1_33680" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_UserDataStopHandler" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_88297" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_CalibStartStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_CalibStopStartStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_CalibStopStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Empty" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ResumeTask" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartFlexSwd" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartNoActTask" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartStopNoIptTask" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StartTask" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopFlexStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartIncFlexStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartIncStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartNoActTask" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStartTask" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopStopwatch" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_StopTask" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_WaitTask" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_Error" To="T1_TraceEventNoSuspTime__" AnnotationSourceType="Manual" Optional="true" />
EOT
        # Functions which call T1_15052
        print $fh <<EOT;
<Indirect FromFunction="T1_56841" To="T1_15052" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_97821" To="T1_15052" AnnotationSourceType="Manual" Optional="true" />
EOT
    }
    else
    {
        # T1_ContResetInternal
        print $fh <<EOT;
<Indirect FromFunction="T1_34149" To="T1_40107" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_70345" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_17659" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_68539" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_01021" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_34149" To="T1_27348" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1.stack memory analyser is supposed to resolve this without annotations. But it does not work for RH850
        # T1_ConfigEventChainPC
        print $fh <<EOT;
<Indirect FromFunction="T1_ConfigEventChainPC" To="T1_06122" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_ScopeOverheadSequenceNoSuspPC
        print $fh <<EOT;
<Indirect FromFunction="T1_ScopeOverheadSequenceNoSuspPC" To="T1_67721" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ScopeOverheadSequenceNoSuspPC" To="T1_94227" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ScopeOverheadSequenceNoSuspPC" To="T1_64751" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_37426
        print $fh <<EOT;
<Indirect FromFunction="T1_37426" To="T1_70345" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_37426" To="T1_27348" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_37539
        print $fh <<EOT;
<Indirect FromFunction="T1_37539" To="T1_01021" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_49569
        print $fh <<EOT;
<Indirect FromFunction="T1_49569" To="T1_70345" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_59506
        print $fh <<EOT;
<Indirect FromFunction="T1_59506" To="T1_55282" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59506" To="T1_99055" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_68569
        print $fh <<EOT;
<Indirect FromFunction="T1_68569" To="T1_93425" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_27017" To="T1_93425" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_71929
        print $fh <<EOT;
<Indirect FromFunction="T1_71929" To="T1_17659" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_75433
        print $fh <<EOT;
<Indirect FromFunction="T1_75433" To="T1_70345" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_83285
        print $fh <<EOT;
<Indirect FromFunction="T1_83285" To="T1_00675" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_59011
        print $fh <<EOT;
<Indirect FromFunction="T1_59011" To="T1_68539" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59011" To="T1_01021" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59011" To="T1_27746" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59011" To="T1_70345" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_59011" To="T1_96630" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_75917
        print $fh <<EOT;
<Indirect FromFunction="T1_75917" To="T1_27746" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_93023
        print $fh <<EOT;
<Indirect FromFunction="T1_93023" To="T1_70345" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_93930
        print $fh <<EOT;
<Indirect FromFunction="T1_93930" To="T1_72583" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_94799
        print $fh <<EOT;
<Indirect FromFunction="T1_94799" To="T1_96630" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_97036
        print $fh <<EOT;
<Indirect FromFunction="T1_97036" To="T1_06122" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_94134
        print $fh <<EOT;
<Indirect FromFunction="T1_94134" To="T1_96630" AnnotationSourceType="Manual" Optional="true" />
EOT
        # T1_74926
        print $fh <<EOT;
<Indirect FromFunction="T1_74926" To="T1_TraceUint32RestNoSusp" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_74926" To="T1_TraceUint32RestNoSuspRC" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_58376" To="T1_TraceUint32RestNoSusp" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_58376" To="T1_TraceUint32RestNoSuspRC" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_91165" To="T1_TraceUint32RestNoSusp" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_91165" To="T1_TraceUint32RestNoSuspRC" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_41949" To="T1_TraceUint32RestNoSusp" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_41949" To="T1_TraceUint32RestNoSuspRC" AnnotationSourceType="Manual" Optional="true" />
EOT

        # T1_56851
        print $fh <<EOT;
<Indirect FromFunction="T1_56851" To="T1_93425" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_26882" To="T1_57687" AnnotationSourceType="Manual" Optional="true" />
EOT

        # For MPC5xxx
        # Functions which call T1_93425
        print $fh <<EOT;
<Indirect FromFunction="T1_56841" To="T1_93425" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_97821" To="T1_93425" AnnotationSourceType="Manual" Optional="true" />
EOT
    }
    # T1.stack memory analyser is supposed to resolve this without annotations. But it does not work for RH850
    # T1_ReceiveFrame_
    print $fh <<EOT;
<Indirect FromFunction="T1_ReceiveFrame_" To="T1_RxBufferRequest" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ReceiveFrame_" To="T1_RxCompleteNotification" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ReceiveFrame_" To="T1_ErrorCallback" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ReceiveFrame_" To="T1_13920" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ReceiveFrame_" To="T1_52041" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_ReceiveFrame_" To="T1_48107" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_13351
    print $fh <<EOT;
<Indirect FromFunction="T1_13351" To="T1_TxCompleteNotification" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13351" To="T1_07139" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_SetStopTriggerNoSuspPC
    print $fh <<EOT;
<Indirect FromFunction="T1_SetStopTriggerNoSuspPC" To="T1_TraceUint32RestNoSuspRC" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_SetStopTriggerNoSuspPC" To="T1_TraceUint32RestNoSuspFg" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_SetStopTriggerNoSuspPC" To="T1_TraceUint32RestNoSusp" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_13591, T1_64715
    print $fh <<EOT;
<Indirect FromFunction="T1_13591" To="T1_TraceUint32RestNoSusp" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_13591" To="T1_TraceUint32RestNoSuspRC" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_64715" To="T1_TraceUint32RestNoSuspFg" AnnotationSourceType="Manual" Optional="true" />
EOT

    # T1_89346
    print $fh <<EOT;
<Indirect FromFunction="T1_89346" To="T1_ErrorCallback" AnnotationSourceType="Manual" Optional="true" />
<Indirect FromFunction="T1_89346" To="T1_52041" AnnotationSourceType="Manual" Optional="true" />
EOT
    ######################################################################################
    # Breakpoint annotations
    ######################################################################################
    foreach my $coreId (0..$config{'nOfCores'} - 1)
    {
        my $fhCoreX = $fhPC[$coreId];
        print $fhCoreX <<EOT;
<Breakpoint FromFunction="T1_83538" To="T1_OuterExceptionHandlerCore${coreId}" Optional="true" />
<Breakpoint FromFunction="T1_83538" To="T1_OuterExceptionHandlerNoOptCore${coreId}" Optional="true" />
<Breakpoint FromFunction="T1_83538" To="T1_OuterExceptionHandler" Optional="true" />
<Breakpoint FromFunction="T1_83538" To="T1_OuterExceptionHandlerNoOpt" Optional="true" />
EOT
    }

    ######################################################################################
    # GlassBox annotations
    ######################################################################################
    print $fh "</Annotations>\n";
    foreach my $coreId (0..$config{'nOfCores'} - 1)
    {
        my $fhCoreX = $fhPC[$coreId];
        print $fhCoreX "</Annotations>\n";
    }
}

1;

