<html>
<head>

	<style>
	.png {behavior:url(/web/20090419143649im_/http://fr.sg.gpotato.eu/Common/Js/iepngfix.htc);} 
	body {
		background:url(game/launcher/bg.jpg) no-repeat;
		padding:0px 0px 0px 0px;
		margin:0px 0px 0px 0px;
		font-size:11px;
		color:#FFFFFF;
		overflow:hidden;
	}

	img {
		border:0;
		padding:0px 0px 0px 0px;
		margin:0px 0px 0px 0px;
	}
	
	#Layout {
		position:relative;
		width:700px;
		height:454px;
	}

	#Layout #Btn1 {
		position:absolute;
		top:125px;
		left:0px;
	}

	#Layout #Btn2 {
		position:absolute;
		top:170px;
		left:0px;
	}

	#Layout #Btn3 {
		position:absolute;
		top:215px;
		left:0px;
	}

	#Layout #Btn4 {
		position:absolute;
		top:425px;
		left:0px;
	}

	#LAUNCH_BUTTON {
		position:absolute;
		top:251px;
		left:5px;
		width:210px;
		height:150px;
	}

	#PROGRESS_1 {
		position:absolute;
		top:396px;
		left:348px;
		width:273px;
		height:3px;
		font-size:3px;
		background:#000000;
	}
	#PROGRESS_2 {
		position:absolute;
		top:400px;
		left:348px;
		width:273px;
		height:4px;
		font-size:4px;
		background:#000000;		
	}

	#PROGRESS_1 .PROGRESS_BAR {
			width:273px;
			height:3px;
	}
	#PROGRESS_1 .PROGRESS_BAR_PRIMARY {
			background-color:#86ffeb; 
			height:3px;
	}
	#PROGRESS_1 .PROGRESS_BAR_SECONDARY {
			background-color:#020205;
			height:3px;
	}

	#PROGRESS_2 .PROGRESS_BAR {
			width:273px;
			height:4px; 
	}
	#PROGRESS_2 .PROGRESS_BAR_PRIMARY {
			background-color:#77e302;
			height:4px; 
	}
	#PROGRESS_2 .PROGRESS_BAR_SECONDARY {
			background-color:#020205;
			height:4px; 
	}

	#PERCENTAGE_1 {
		position:absolute;
		top:393px;
		left:627px;
		width:30px;
		height:15px;
		color:#805EA6;
	}
	#PERCENTAGE_2 {
		position:absolute;
		top:393px;
		left:660px;
		width:30px;
		height:15px;
		color:#805EA6;
	}

	#MESSAGE {
		position:absolute;
		top:404px;
		left:348px;
		width:300px;
		height:15px;
		color:#805EA6;
		font-size:10px;
	}
	#FILENAME {
		position:absolute;
		top:404px;
		left:348px;
		width:300px;
		height:15px;
		color:#805EA6;
		font-size:10px;
	}

	.PRIMARY_FONT {
        color: white;
		font-size:10px;
	}
	.SECONDARY_FONT {
		color: white;
		font-size:10px;
	}

	#DivMenu {
		position:absolute;
		top:261px;
		left:297px;
	}

	#DivBan {
		position:absolute;
		top:23px;
		left:298px;
	}

	#DivClose {
		position:absolute;
		top:5px;
		left:680px;
	}

	td {
		color:#805EA6;
		font-size:11px;
		font-family:arial;
		padding-left:10px;
	}

	.Info {
		position:absolute;
		top:283px;
		left:297px;
		width:386;
		height:106;
		background:url(game/launcher/news_bg.jpg);
	}

	.Info td {
		color:#4B5E73;
		font-size:11px;
		font-family:arial;
		padding-left:10px;
	}

	a			{text-decoration:none;color:#4B5E73; font-size:11px; font-family:arial;}
	a:hovor		{text-decoration:none;color:#4B5E73; font-size:11px; font-family:arial;}
	a:visited	{text-decoration:none;color:#4B5E73; font-size:11px; font-family:arial;}
	a:active	{text-decoration:none;color:#4B5E73; font-size:11px; font-family:arial;}
	
	</style>

	<script language="JavaScript">
	<!-- 
	function FnSel(sType)
	{
		var objNews = document.getElementById("DivNews");
		var objUpd	= document.getElementById("DivUpd");
		var objEvt	= document.getElementById("DivEvt");

		var objImgNews	= document.getElementById("ImgNews");
		var objImgUpd	= document.getElementById("ImgUpd");
		var objImgEvt	= document.getElementById("ImgEvt");

		objNews.style.display	= "none";
		objUpd.style.display	= "none";
		objEvt.style.display	= "none";

		objImgNews.src	= "game/launcher/news_bt1.jpg";
		objImgUpd.src	= "game/launcher/news_bt2.jpg";
		objImgEvt.src	= "game/launcher/news_bt3.jpg";
		
		switch(sType)
		{
			case "N":
				objNews.style.display = "inline";
				objImgNews.src	= "game/launcher/news_bt1on.jpg";
			break;
			case "U":
				objUpd.style.display = "inline";
				objImgUpd.src	= "game/launcher/news_bt2on.jpg";
			break;
			default:
				objEvt.style.display = "inline";
				objImgEvt.src	= "game/launcher/news_bt3on.jpg";
			break;
		}
	}
	//-->
	</script>
</head>
<body>

<style type="text/css">
body {
  margin-top:0 !important;
  padding-top:0 !important;
  min-width:800px !important;
}
</style>


<div id="Layout">
	<div id="Btn1"><a href="/web/20090419143649/http://fr.gpotato.eu/Account/AccReg.aspx"	target="_blank" onfocus="blur()"><img src="common/blank.gif" width="145" height="35"/></a></div>
	<div id="Btn2"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/"					target="_blank" onfocus="blur()"><img src="common/blank.gif" width="145" height="35"/></a></div>
	<div id="Btn3"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum"				target="_blank" onfocus="blur()"><img src="common/blank.gif" width="145" height="35"/></a></div>
	<div id="Btn4"><a href="/web/20090419143649/http://fr.gpotato.eu/"						target="_blank" onfocus="blur()"><img src="common/blank.gif" width="130" height="25"/></a></div>
	<div id="DivClose">
	<a href="action://DESTROY/" onfocus="blur()"><img src="game/launcher/close_bt.jpg" /></a>
	</div>
	<div id="DivMenu">
	<a href="#" onclick="FnSel('N')"><img src="game/launcher/news_bt1on.jpg" id="ImgNews"/></a><a href="#" onclick="FnSel('U')"><img src="game/launcher/news_bt2.jpg" id="ImgUpd" /></a><a href="#" onclick="FnSel('E')"><img src="game/launcher/news_bt3.jpg" id="ImgEvt" /></a>
	</div>
	<div id="DivBan">
	<img src="game/launcher/easter_banner.jpg" />
	<!--<img src="game/launcher/asian_banner.jpg" />-->
	<!--<img src="game/launcher/openbeta_banner.jpg" />-->
	<!--<img src="game/launcher/gmdays_banner_fr.jpg" />-->
	</div>
	<div id="DivNews" class="Info" style="padding-top:6">
	<table cellpadding="0" cellspacing="0">
	
	<tr height="18">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N001&amp;MODE=VT&amp;TNO=29" target="_blank">Joyeuses P&#226;ques</a></td>
		<td width="60">09.Apr.2009</td>
	</tr>
	
	<tr height="18">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N001&amp;MODE=VT&amp;TNO=28" target="_blank">Lancement officiel</a></td>
		<td width="60">05.Mar.2009</td>
	</tr>
	
	<tr height="18">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N001&amp;MODE=VT&amp;TNO=27" target="_blank">Nouveaux v&#234;tements !</a></td>
		<td width="60">05.Mar.2009</td>
	</tr>
	
	<tr height="18">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N001&amp;MODE=VT&amp;TNO=24" target="_blank">Fin du b&#234;ta test ouvert</a></td>
		<td width="60">27.Feb.2009</td>
	</tr>
	
	<tr height="18">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N001&amp;MODE=VT&amp;TNO=22" target="_blank">Nouveaux v&#234;tements !</a></td>
		<td width="60">12.Feb.2009</td>
	</tr>
	
	</table>
	</div>
	<div id="DivUpd" class="Info" style="display:none" style="padding-top:6">
	<table>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N003&amp;MODE=VT&amp;TNO=30" target="_blank">La chasse aux oeufs</a></td>
		<td width="60">08.Apr.2009</td>
	</tr>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N003&amp;MODE=VT&amp;TNO=29" target="_blank">Tournoi de P&#226;ques</a></td>
		<td width="60">08.Apr.2009</td>
	</tr>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N003&amp;MODE=VT&amp;TNO=28" target="_blank">Quiz de P&#226;ques</a></td>
		<td width="60">03.Apr.2009</td>
	</tr>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N003&amp;MODE=VT&amp;TNO=27" target="_blank">Tournoi Back Street</a></td>
		<td width="60">20.Mar.2009</td>
	</tr>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N003&amp;MODE=VT&amp;TNO=26" target="_blank">Pleine vitesse &#224; Park Town</a></td>
		<td width="60">04.Mar.2009</td>
	</tr>
	
	</table>
	</div>
	
	<div id="DivEvt" class="Info" style="display:none" style="padding-top:6">
	<table>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N002&amp;MODE=VT&amp;TNO=17" target="_blank">Note de mise &#224; jour du 19/03/2009</a></td>
		<td width="60">19.Mar.2009</td>
	</tr>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N002&amp;MODE=VT&amp;TNO=16" target="_blank">Note de mise &#224; jour du 11/03/2009</a></td>
		<td width="60">11.Mar.2009</td>
	</tr>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N002&amp;MODE=VT&amp;TNO=15" target="_blank">D&#233;fi Absolu - Note de mise &#224; jour</a></td>
		<td width="60">05.Mar.2009</td>
	</tr>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N002&amp;MODE=VT&amp;TNO=14" target="_blank">Note de mise &#224; jour du 19/02/2009</a></td>
		<td width="60">19.Feb.2009</td>
	</tr>
	
	<tr height="15">
		<td width="295"><a href="/web/20090419143649/http://fr.sg.gpotato.eu/Forum/Index.aspx?FCD=SG_FR_N002&amp;MODE=VT&amp;TNO=13" target="_blank">Note de mise &#224; jour du 12/02/2009</a></td>
		<td width="60">12.Feb.2009</td>
	</tr>
	
	</table>
	</div>

	<SPAN id=START_BUTTON></SPAN>
	<SPAN id=LAUNCH_BUTTON></SPAN>
	<SPAN id=PROGRESS_1></SPAN>
	<SPAN id=PROGRESS_2></SPAN>
	<SPAN id=PERCENTAGE_1></SPAN>
	<SPAN id=PERCENTAGE_2></SPAN>
	<SPAN id=MESSAGE></SPAN>
	<SPAN id=FILENAME></SPAN>
</div>
<script>FnSel('U');</script>
</body>
</html>