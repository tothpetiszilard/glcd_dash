<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.2.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="yes" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="yes" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="yes" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="yes" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="yes" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="yes" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="yes" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="yes" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="yes" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="yes" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="yes" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="yes" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="yes" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="yes" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="yes" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="yes" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="yes" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="yes" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="yes" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="yes" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="yes" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="yes" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="jumper">
<description>&lt;b&gt;Jumpers&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="JP4">
<description>&lt;b&gt;JUMPER&lt;/b&gt;</description>
<wire x1="-5.08" y1="-1.016" x2="-5.08" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.27" x2="0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="1.016" x2="0.254" y2="1.27" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.27" x2="0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.016" x2="0.254" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.286" y1="-1.27" x2="2.54" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.286" y1="1.27" x2="2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="1.27" x2="0" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="1.27" x2="-2.286" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.016" x2="-2.286" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="1.27" x2="-2.54" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.016" x2="-4.826" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="1.27" x2="-4.826" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-1.27" x2="0" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.016" x2="-2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="-1.27" x2="-2.54" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.016" x2="-4.826" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-1.27" x2="-2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.794" y1="-1.27" x2="-4.826" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.016" x2="5.08" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="4.826" y1="1.27" x2="5.08" y2="1.016" width="0.1524" layer="21"/>
<wire x1="4.826" y1="-1.27" x2="5.08" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.016" x2="2.794" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.016" x2="2.794" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.826" y1="1.27" x2="2.794" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.826" y1="-1.27" x2="2.794" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="0.9144" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="0" drill="0.9144" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="0" drill="0.9144" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="0" drill="0.9144" shape="long" rot="R90"/>
<text x="-5.08" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.81" y="-2.667" size="0.9906" layer="21" ratio="12">1</text>
<text x="-1.27" y="-2.667" size="0.9906" layer="21" ratio="12">2</text>
<text x="1.27" y="-2.667" size="0.9906" layer="21" ratio="12">3</text>
<text x="3.81" y="-2.667" size="0.9906" layer="21" ratio="12">4</text>
<text x="-5.08" y="-4.064" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-4.1148" y1="-0.3048" x2="-3.5052" y2="0.3048" layer="51"/>
<rectangle x1="-1.5748" y1="-0.3048" x2="-0.9652" y2="0.3048" layer="51"/>
<rectangle x1="0.9652" y1="-0.3048" x2="1.5748" y2="0.3048" layer="51"/>
<rectangle x1="3.5052" y1="-0.3048" x2="4.1148" y2="0.3048" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="JP4E">
<wire x1="2.54" y1="0" x2="2.54" y2="1.27" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="1.27" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="1.27" width="0.1524" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="1.27" width="0.4064" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="1.27" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="1.27" width="0.4064" layer="94"/>
<wire x1="-3.175" y1="0" x2="5.08" y2="0" width="0.4064" layer="94"/>
<wire x1="5.08" y1="0" x2="5.715" y2="0" width="0.4064" layer="94"/>
<wire x1="5.715" y1="0" x2="5.715" y2="0.635" width="0.4064" layer="94"/>
<wire x1="5.715" y1="0.635" x2="-3.175" y2="0.635" width="0.4064" layer="94"/>
<wire x1="-3.175" y1="0.635" x2="-3.175" y2="0" width="0.4064" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="1.27" width="0.4064" layer="94"/>
<wire x1="5.08" y1="0" x2="5.08" y2="1.27" width="0.1524" layer="94"/>
<text x="-3.81" y="0" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="8.255" y="0" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="1" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" rot="R90"/>
<pin name="2" x="0" y="-2.54" visible="pad" length="short" direction="pas" rot="R90"/>
<pin name="3" x="2.54" y="-2.54" visible="pad" length="short" direction="pas" rot="R90"/>
<pin name="4" x="5.08" y="-2.54" visible="pad" length="short" direction="pas" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="JP4E" prefix="JP" uservalue="yes">
<description>&lt;b&gt;JUMPER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="JP4E" x="0" y="0"/>
</gates>
<devices>
<device name="" package="JP4">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-hirose">
<description>&lt;b&gt;Hirose Connectors&lt;/b&gt;&lt;p&gt;
www.hirose.co.jp&lt;p&gt;
Include : &lt;br&gt;
con-hirose-df12d(3.0)60dp0.5v80.lbr from Bob Starr &amp;lt;rtzaudio@mindspring.com&amp;gt;&lt;br&gt;
con-hirose.lbr from Bob Starr &amp;lt;rtzaudio@mindspring.com&amp;gt;&lt;br&gt;</description>
<packages>
<package name="FH12-08S-1SH">
<wire x1="-5.7" y1="0.5" x2="-6.2" y2="0.5" width="0.2032" layer="51"/>
<wire x1="-6.2" y1="0.5" x2="-6.2" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="-6.2" y1="-0.5" x2="-5.7" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="-5.7" y1="-0.5" x2="-5.7" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-5.7" y1="-1.9" x2="-5.4" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="-5.4" y1="-1.9" x2="-5.4" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-5.4" y1="-2.2" x2="-5.7" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-5.7" y1="-2.2" x2="-5.7" y2="-2.9" width="0.2032" layer="21"/>
<wire x1="5.7" y1="-2.9" x2="5.7" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="5.7" y1="-2.2" x2="5.4" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="5.4" y1="-2.2" x2="5.4" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="5.4" y1="-1.9" x2="5.7" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="5.7" y1="-1.9" x2="5.7" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="5.7" y1="-0.5" x2="6.2" y2="-0.5" width="0.2032" layer="51"/>
<wire x1="6.2" y1="-0.5" x2="6.2" y2="0.5" width="0.2032" layer="51"/>
<wire x1="6.2" y1="0.5" x2="5.7" y2="0.5" width="0.2032" layer="51"/>
<wire x1="5.7" y1="0.5" x2="5.7" y2="2.5" width="0.2032" layer="51"/>
<wire x1="5.7" y1="2.5" x2="-5.7" y2="2.5" width="0.2032" layer="51"/>
<wire x1="-5.7" y1="2.5" x2="-5.7" y2="0.5" width="0.2032" layer="51"/>
<wire x1="5.4" y1="-1.9" x2="-5.4" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="5.7" y1="-2.9" x2="-5.7" y2="-2.9" width="0.2032" layer="21"/>
<wire x1="-5.7" y1="2.5" x2="-5.7" y2="1.5" width="0.2032" layer="21"/>
<wire x1="-4" y1="2.5" x2="-5.7" y2="2.5" width="0.2032" layer="21"/>
<wire x1="5.7" y1="1.5" x2="5.7" y2="2.5" width="0.2032" layer="21"/>
<wire x1="5.7" y1="2.5" x2="4" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-5.7" y1="-1.5" x2="-5.7" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="5.7" y1="-1.9" x2="5.7" y2="-1.5" width="0.2032" layer="21"/>
<smd name="1" x="-3.5" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="2" x="-2.5" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="3" x="-1.5" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="4" x="-0.5" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="5" x="0.5" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="6" x="1.5" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="7" x="2.5" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<smd name="8" x="3.5" y="3.25" dx="0.3" dy="1.3" layer="1" stop="no" cream="no"/>
<text x="-5.1976" y="4.095" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.9976" y="-0.3258" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-3.7" y1="2.55" x2="-3.3" y2="3.95" layer="29"/>
<rectangle x1="-3.625" y1="2.625" x2="-3.375" y2="3.875" layer="31"/>
<rectangle x1="-2.7" y1="2.55" x2="-2.3" y2="3.95" layer="29"/>
<rectangle x1="-2.625" y1="2.625" x2="-2.375" y2="3.875" layer="31"/>
<rectangle x1="-1.7" y1="2.55" x2="-1.3" y2="3.95" layer="29"/>
<rectangle x1="-1.625" y1="2.625" x2="-1.375" y2="3.875" layer="31"/>
<rectangle x1="-0.7" y1="2.55" x2="-0.3" y2="3.95" layer="29"/>
<rectangle x1="-0.625" y1="2.625" x2="-0.375" y2="3.875" layer="31"/>
<rectangle x1="0.3" y1="2.55" x2="0.7" y2="3.95" layer="29"/>
<rectangle x1="0.375" y1="2.625" x2="0.625" y2="3.875" layer="31"/>
<rectangle x1="1.3" y1="2.55" x2="1.7" y2="3.95" layer="29"/>
<rectangle x1="1.375" y1="2.625" x2="1.625" y2="3.875" layer="31"/>
<rectangle x1="2.3" y1="2.55" x2="2.7" y2="3.95" layer="29"/>
<rectangle x1="2.375" y1="2.625" x2="2.625" y2="3.875" layer="31"/>
<rectangle x1="3.3" y1="2.55" x2="3.7" y2="3.95" layer="29"/>
<rectangle x1="3.375" y1="2.625" x2="3.625" y2="3.875" layer="31"/>
<rectangle x1="5" y1="-1.1" x2="6.8" y2="1.1" layer="1" rot="R180"/>
<rectangle x1="4.95" y1="-1.175" x2="6.85" y2="1.175" layer="29" rot="R180"/>
<rectangle x1="5.075" y1="-1.025" x2="6.725" y2="1.025" layer="31" rot="R180"/>
<rectangle x1="-6.8" y1="-1.1" x2="-5" y2="1.1" layer="1" rot="R180"/>
<rectangle x1="-6.85" y1="-1.175" x2="-4.95" y2="1.175" layer="29" rot="R180"/>
<rectangle x1="-6.725" y1="-1.025" x2="-5.075" y2="1.025" layer="31" rot="R180"/>
<rectangle x1="-3.6" y1="2.55" x2="-3.4" y2="3.4" layer="51"/>
<rectangle x1="-2.6" y1="2.55" x2="-2.4" y2="3.4" layer="51"/>
<rectangle x1="-1.6" y1="2.55" x2="-1.4" y2="3.4" layer="51"/>
<rectangle x1="-0.6" y1="2.55" x2="-0.4" y2="3.4" layer="51"/>
<rectangle x1="0.4" y1="2.55" x2="0.6" y2="3.4" layer="51"/>
<rectangle x1="1.4" y1="2.55" x2="1.6" y2="3.4" layer="51"/>
<rectangle x1="2.4" y1="2.55" x2="2.6" y2="3.4" layer="51"/>
<rectangle x1="3.4" y1="2.55" x2="3.6" y2="3.4" layer="51"/>
<polygon width="0.2032" layer="21">
<vertex x="-3.7" y="-2.2"/>
<vertex x="-3.5" y="-2.6"/>
<vertex x="-3.3" y="-2.2"/>
</polygon>
</package>
</packages>
<symbols>
<symbol name="PINV">
<wire x1="0" y1="0.254" x2="0" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="0" y1="-0.254" x2="1.016" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-0.254" x2="1.27" y2="0.254" width="0.1524" layer="94"/>
<wire x1="1.27" y1="0.254" x2="0" y2="0.254" width="0.1524" layer="94"/>
<text x="2.032" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="PIN">
<wire x1="0" y1="0.254" x2="0" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="0" y1="-0.254" x2="1.016" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-0.254" x2="1.27" y2="0.254" width="0.1524" layer="94"/>
<wire x1="1.27" y1="0.254" x2="0" y2="0.254" width="0.1524" layer="94"/>
<text x="2.032" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FH12-08S-1S" prefix="X">
<description>&lt;b&gt;1mm Pitch Connectors For FPC/FFC&lt;/b&gt;&lt;p&gt;
Source: &lt;a href= "http://www.hirose.co.jp/cataloge_hp/e58605370.pdf"&gt;Data sheet&lt;/a&gt;&lt;p&gt;</description>
<gates>
<gate name="-1" symbol="PINV" x="0" y="7.62" addlevel="always"/>
<gate name="-2" symbol="PIN" x="0" y="5.08" addlevel="always"/>
<gate name="-3" symbol="PIN" x="0" y="2.54" addlevel="always"/>
<gate name="-4" symbol="PIN" x="0" y="0" addlevel="always"/>
<gate name="-5" symbol="PIN" x="0" y="-2.54" addlevel="always"/>
<gate name="-6" symbol="PIN" x="0" y="-5.08" addlevel="always"/>
<gate name="-7" symbol="PIN" x="0" y="-7.62" addlevel="always"/>
<gate name="-8" symbol="PIN" x="0" y="-10.16" addlevel="always"/>
</gates>
<devices>
<device name="H" package="FH12-08S-1SH">
<connects>
<connect gate="-1" pin="1" pad="1"/>
<connect gate="-2" pin="1" pad="2"/>
<connect gate="-3" pin="1" pad="3"/>
<connect gate="-4" pin="1" pad="4"/>
<connect gate="-5" pin="1" pad="5"/>
<connect gate="-6" pin="1" pad="6"/>
<connect gate="-7" pin="1" pad="7"/>
<connect gate="-8" pin="1" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="JP1" library="jumper" deviceset="JP4E" device=""/>
<part name="JP2" library="jumper" deviceset="JP4E" device=""/>
<part name="JP3" library="jumper" deviceset="JP4E" device=""/>
<part name="JP4" library="jumper" deviceset="JP4E" device=""/>
<part name="JP5" library="jumper" deviceset="JP4E" device=""/>
<part name="JP6" library="jumper" deviceset="JP4E" device=""/>
<part name="X2" library="con-hirose" deviceset="FH12-08S-1S" device="H"/>
<part name="X3" library="con-hirose" deviceset="FH12-08S-1S" device="H"/>
<part name="X4" library="con-hirose" deviceset="FH12-08S-1S" device="H"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="JP1" gate="G$1" x="-10.16" y="76.2" rot="R90"/>
<instance part="JP2" gate="G$1" x="-10.16" y="66.04" rot="R90"/>
<instance part="JP3" gate="G$1" x="-10.16" y="55.88" rot="R90"/>
<instance part="JP4" gate="G$1" x="-10.16" y="45.72" rot="R90"/>
<instance part="JP5" gate="G$1" x="-10.16" y="35.56" rot="R90"/>
<instance part="JP6" gate="G$1" x="-10.16" y="25.4" rot="R90"/>
<instance part="X2" gate="-1" x="17.78" y="81.28"/>
<instance part="X2" gate="-2" x="17.78" y="78.74"/>
<instance part="X2" gate="-3" x="17.78" y="76.2"/>
<instance part="X2" gate="-4" x="17.78" y="73.66"/>
<instance part="X2" gate="-5" x="17.78" y="71.12"/>
<instance part="X2" gate="-6" x="17.78" y="68.58"/>
<instance part="X2" gate="-7" x="17.78" y="66.04"/>
<instance part="X2" gate="-8" x="17.78" y="63.5"/>
<instance part="X3" gate="-1" x="17.78" y="60.96"/>
<instance part="X3" gate="-2" x="17.78" y="58.42"/>
<instance part="X3" gate="-3" x="17.78" y="55.88"/>
<instance part="X3" gate="-4" x="17.78" y="53.34"/>
<instance part="X3" gate="-5" x="17.78" y="50.8"/>
<instance part="X3" gate="-6" x="17.78" y="48.26"/>
<instance part="X3" gate="-7" x="17.78" y="45.72"/>
<instance part="X3" gate="-8" x="17.78" y="43.18"/>
<instance part="X4" gate="-1" x="17.78" y="40.64"/>
<instance part="X4" gate="-2" x="17.78" y="38.1"/>
<instance part="X4" gate="-3" x="17.78" y="35.56"/>
<instance part="X4" gate="-4" x="17.78" y="33.02"/>
<instance part="X4" gate="-5" x="17.78" y="30.48"/>
<instance part="X4" gate="-6" x="17.78" y="27.94"/>
<instance part="X4" gate="-7" x="17.78" y="25.4"/>
<instance part="X4" gate="-8" x="17.78" y="22.86"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="4"/>
<wire x1="-7.62" y1="81.28" x2="15.24" y2="81.28" width="0.1524" layer="91"/>
<pinref part="X2" gate="-1" pin="1"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="3"/>
<wire x1="-7.62" y1="78.74" x2="15.24" y2="78.74" width="0.1524" layer="91"/>
<pinref part="X2" gate="-2" pin="1"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="2"/>
<wire x1="-7.62" y1="76.2" x2="15.24" y2="76.2" width="0.1524" layer="91"/>
<pinref part="X2" gate="-3" pin="1"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="1"/>
<wire x1="-7.62" y1="73.66" x2="15.24" y2="73.66" width="0.1524" layer="91"/>
<pinref part="X2" gate="-4" pin="1"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="4"/>
<wire x1="-7.62" y1="71.12" x2="15.24" y2="71.12" width="0.1524" layer="91"/>
<pinref part="X2" gate="-5" pin="1"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="3"/>
<wire x1="-7.62" y1="68.58" x2="15.24" y2="68.58" width="0.1524" layer="91"/>
<pinref part="X2" gate="-6" pin="1"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="2"/>
<wire x1="-7.62" y1="66.04" x2="15.24" y2="66.04" width="0.1524" layer="91"/>
<pinref part="X2" gate="-7" pin="1"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="JP2" gate="G$1" pin="1"/>
<wire x1="-7.62" y1="63.5" x2="15.24" y2="63.5" width="0.1524" layer="91"/>
<pinref part="X2" gate="-8" pin="1"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="4"/>
<wire x1="-7.62" y1="60.96" x2="15.24" y2="60.96" width="0.1524" layer="91"/>
<pinref part="X3" gate="-1" pin="1"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="3"/>
<wire x1="-7.62" y1="58.42" x2="15.24" y2="58.42" width="0.1524" layer="91"/>
<pinref part="X3" gate="-2" pin="1"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="2"/>
<wire x1="-7.62" y1="55.88" x2="15.24" y2="55.88" width="0.1524" layer="91"/>
<pinref part="X3" gate="-3" pin="1"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="JP3" gate="G$1" pin="1"/>
<wire x1="-7.62" y1="53.34" x2="15.24" y2="53.34" width="0.1524" layer="91"/>
<pinref part="X3" gate="-4" pin="1"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="4"/>
<wire x1="-7.62" y1="50.8" x2="15.24" y2="50.8" width="0.1524" layer="91"/>
<pinref part="X3" gate="-5" pin="1"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="3"/>
<wire x1="-7.62" y1="48.26" x2="15.24" y2="48.26" width="0.1524" layer="91"/>
<pinref part="X3" gate="-6" pin="1"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="2"/>
<wire x1="-7.62" y1="45.72" x2="15.24" y2="45.72" width="0.1524" layer="91"/>
<pinref part="X3" gate="-7" pin="1"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="JP4" gate="G$1" pin="1"/>
<wire x1="-7.62" y1="43.18" x2="15.24" y2="43.18" width="0.1524" layer="91"/>
<pinref part="X3" gate="-8" pin="1"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="JP5" gate="G$1" pin="4"/>
<wire x1="-7.62" y1="40.64" x2="15.24" y2="40.64" width="0.1524" layer="91"/>
<pinref part="X4" gate="-1" pin="1"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="JP5" gate="G$1" pin="3"/>
<wire x1="-7.62" y1="38.1" x2="15.24" y2="38.1" width="0.1524" layer="91"/>
<pinref part="X4" gate="-2" pin="1"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="JP5" gate="G$1" pin="2"/>
<wire x1="-7.62" y1="35.56" x2="15.24" y2="35.56" width="0.1524" layer="91"/>
<pinref part="X4" gate="-3" pin="1"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="JP5" gate="G$1" pin="1"/>
<wire x1="-7.62" y1="33.02" x2="15.24" y2="33.02" width="0.1524" layer="91"/>
<pinref part="X4" gate="-4" pin="1"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="JP6" gate="G$1" pin="4"/>
<wire x1="-7.62" y1="30.48" x2="15.24" y2="30.48" width="0.1524" layer="91"/>
<pinref part="X4" gate="-5" pin="1"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="JP6" gate="G$1" pin="3"/>
<wire x1="-7.62" y1="27.94" x2="15.24" y2="27.94" width="0.1524" layer="91"/>
<pinref part="X4" gate="-6" pin="1"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="JP6" gate="G$1" pin="2"/>
<wire x1="-7.62" y1="25.4" x2="15.24" y2="25.4" width="0.1524" layer="91"/>
<pinref part="X4" gate="-7" pin="1"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="JP6" gate="G$1" pin="1"/>
<wire x1="-7.62" y1="22.86" x2="15.24" y2="22.86" width="0.1524" layer="91"/>
<pinref part="X4" gate="-8" pin="1"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
