const char *HIST_MONTH_STRING = "<!DOCTYPE html><html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta charset=\"UTF-8\"><title>Current Conditions</title><link href=\"magnum_style.css\" rel=\"stylesheet\" type=\"text/css\"><link rel=\"icon\" type=\"images/favicon\" href=\"data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAD///8A////AP///wD///8A3ub4H3Cc7Y650PXwy9z4/wBZ7v8wcu3PYI3sn87Z9jD///8A////AP///wD///8A////AP///wDu8vsPcKDujgBm7/8Ab/j/fbf7//r6+v8AcP7/AGv8/wBk+P8AWPD/cJjuju7x+w////8A////AP///wD///8AMH/qzwB29/8Af/3/AIH//16v/f/6+vr/L5P+/wB3//8Acv//AGv9/wBg9/8wb+vP7vH7D////wD///8AcKftjgB99v8Aif7/AI3//wCO//8/qP7/+vr6/06q/f8Agf//AHr//wB0//8Abf7/AGD3/2CO7Z////8A3un4HwB77/8AkP3/AJf//wCa//8Am///AJr///r6+v99xvz/AIv//wCE//8AfP//AHT//wBs/v8AWfH/vs30P3Ct7Y4Ajvf/AJ3//wCk//8Ap///AKn//wCn///b7/v/rN38/wCW//8Ajf//AIT//wB6//8Acv//AGX5/2CO7Z9utvHPP7T7/z+9/v8/w/7/P8b+/z/H/v8/xv7/u+f7/7vm+/8vsf7/P6/+/z+n/v8/n/7/P5j+/z+P+/9jlPHb+vr6//r6+v/6+vr/+vr6//r6+v/6+vr/+vr6/7vq+//6+vr/u+b7//r6+v/6+vr/+vr6//r6+v/6+vr/+vr6/7vg9/+75/v/u+r7/7vt+/+77vv/+vr6//r6+v+s6fz/+vr6/5ze/P/6+vr/6vT6/7ve+/+72/v/u9j7/7vS9//h8Pj3+vr6//r6+v/6+vr/+vr6//r6+v/6+vr/u+77//r6+v+c4Pz/+vr6//r6+v/6+vr/+vr6//r6+v/6+vr/vd/0z/r6+v/6+vr/+vr6//r6+v/6+vr/+vr6/6zs/P/6+vr/u+n7//r6+v/6+vr/+vr6//r6+v/6+vr/ydj24OTw+Ve75ff/u+v7/7vu+/+78Pv/u/H7/7vw+/+M5fz/6vb6/5zg/P+75fv/u+L7/7vf+/+72/v/u9X3/9zk93D///8AcMHtjgCy9v8AxP7/AMv//wDO//8Ay///AMX//7vq+/+75/v/AKT//wCX//8Aif7/AHb3/3Cg7o7///8A////AP///wAwrOrPALL2/wC//f8Aw///AMH//wC7//991/z/2/D7/wCd//8AkP3/AH73/zCA68/u8vsP////AP///wD///8A////AHDB7Y4Ape//AK73/wCx+/8Ar/7/P739/9vu+v8Ajvf/AHvv/3Cn7o7u8vsP////AP///wD///8A////AP///wD///8A3u34H3C97Y5ArO6/AJPu/xCT7//6+vr/cK3tjt7p+B////8A////AP///wD///8A+B8AAOAHAADAAwAAgAEAAIABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACAAQAAgAEAAMADAADgBwAA+B8AAA==\"></head><body style=\"background-color:#fff;margin-top:0\"><div id=\"wrapper\" style=\"width:100%;margin-left:auto;margin-right:auto;background-color:#fff\"><div><div id=\"header\" style=\"width:100%\"><a href=\"http://www.solarstik.com/\"><img src=\"data:image/png;base64,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\" alt=\"Solar Stik\" style=\"text-decoration:none;border:none;outline:0;padding-bottom:5px;padding-top:30px;padding-left:5px\"></a><b style=\"padding-left:20px\">24/7 Support: 800-793-4364 Ext 102</b></div><div class=\"navBarCon\"><ul style=\"border:none;width:100%;border-spacing:0;list-style-type:none\"><li><a href=\"/\">Current Conditions</a></li><li><a href=\"currentSettings.html\">Current Settings</a></li><li><a href=\"/historical\">Historical Data</a></li></ul></div></div></div><div style=\"text-align:center\"><h1 id=\"headline\">Historical Data</h1><br></div><script>window.console||(console={log:function(){}})</script><script type=\"text/javascript\" src=\"jquery-1.11.1.min.js\"></script><script type=\"text/javascript\" src=\"excanvas.min.js\"></script><script type=\"text/javascript\" src=\"jquery.flot.js\"></script><script type=\"text/javascript\" src=\"jquery.flot.threshold.js\"></script><script type=\"text/javascript\" src=\"howler.min.js\"></script><script type=\"text/javascript\" src=\"jquery.getUrlParam.js\"></script><script type=\"text/javascript\" src=\"date.js\"></script><script type=\"text/javascript\" src=\"magnum.js\"></script><script>var loadTimer,tenMinAvg=[],now=0,calMonths=[0,\"January\",\"Feburary\",\"March\",\"April\",\"May\",\"June\",\"July\",\"August\",\"September\",\"October\",\"November\",\"December\"];function loadHeadline(){var e=new XMLHttpRequest;e.onreadystatechange=function(){if(e.readyState===XMLHttpRequest.DONE)if(200===e.status){var t=JSON.parse(e.responseText);$(\"#headline\").html(t.hostname+\": Historical Data\")}else console.error(\"Error:\",e.status)},e.open(\"GET\",\"/hostinfo.json\",!0),e.send()}$(document).ready(function(){\"iPhone\"!=navigator.platform&&\"iPod\"!=navigator.platform||$(\"#bar\").hide(),$(window).focus(function(){}),$(document).ajaxError(function(t){$(\"#connection_warn\").show(),$(\"#connection_warn\").append(t)}),loadHeadline(),loadChannels()});var date,oldestTime,mostRecentTime,summaryAr,channels,dataAr=[],chargeAr=[],flot=[],flot1=[],flot2=[],flot3=[],flot4=[];function loadChannels(){var t=new XMLHttpRequest;t.onreadystatechange=function(){t.readyState===XMLHttpRequest.DONE&&(200===t.status?(dataS=$.parseJSON(t.responseText),channels=dataS.data,getFiles()):(console.error(\"Error:\",t.status),noResponse=!0,customFaults(null)))},t.open(\"GET\",\"/channel.json\",!0),t.send()}function getChObj(t){for(var e=0;e<channels.length;e++)if(channels[e].id==t)return channels[e];return null}function getSumChannels(){for(var t=[],e=0;e<channels.length;e++)null!=channels[e].historyByDay&&\"true\"==channels[e].historyByDay&&t.push(channels[e].id);return t}function loadSummary(){if(isIE){var t=new XDomainRequest;t.open(\"get\",urlSummary+\"?t=\"+(new Date).getTime()),t.onload=function(){\"\"==t.responseText?($(\"#files\").html(\"\"),$(\"#lH1\").html(\"Summary not available at this time. Try again in a couple minutes.\"),$(\"#loading\").show(),setTimeout(loadSummary,1e4)):(dataS=$.parseJSON(t.responseText),processSum(dataS))},t.send()}else $.ajaxSetup({cache:!1}),$.ajax({type:\"GET\",url:urlSummary,dataType:\"html\",crossDomain:!0}).done(function(t){null==t?($(\"#files\").html(\"\"),$(\"#lH1\").html(\"Summary not available at this time. Try again in a couple minutes.\"),$(\"#loading\").show(),setTimeout(loadSummary,1e4)):processSum(t=$.parseJSON(t))})}function processSum(t){summaryAr=t.summary_stats,getFiles()}function getFiles(){var t=new XMLHttpRequest;t.onreadystatechange=function(){t.readyState===XMLHttpRequest.DONE&&(200===t.status?(dataS=JSON.parse(t.responseText),processFiles(dataS)):console.error(\"Error:\",t.status))},t.open(\"GET\",\"/historyFiles.json\",!0),t.send()}function processFiles(t){var e=t.history_files.files,n=\"\",a=\"\",s=[],r=[],o=$(document).getUrlParam(\"months[]\");if(e.sort(),null==o){o=[];for(var l=0;l<e.length&&!(11<o.length);l++){var i=e[l].substring(0,6);console.log($.inArray(i,o)),-1==$.inArray(i,o)&&o.push(i)}}console.log(o);for(var u=3*getSumChannels().length+3,c=e.length-1;0<=c;c--){(isIE&&o instanceof Array?-1!=jQuery.inArray(e[c].substr(0,6),o):-1!=o.indexOf(e[c].substr(0,6)))&&(isNaN(e[c].substr(0,4))||(n!=e[c].substr(0,4)&&(n=e[c].substr(0,4),s.push(e[c].substr(0,4)),a=0),a!=e[c].substr(4,2)&&(a=e[c].substr(4,2),null==r[n]&&(r[n]=[]),r[n].push(e[c].substr(4,2)),$(\"#files\").append(\"<tr><th colspan=\"+u+\">\"+calMonths[parseInt(e[c].substr(4,2),10)]+\" - \"+e[c].substr(0,4)+\"</th></div></tr>\"),$(\"#files\").append(\"<tr><th rowspan=2>Date</th><th rowspan=2>Download</th><th rowspan=2>Delete</th></tr>\")),$(\"#files\").append(getRow(e[c]))))}$(\"#loading\").hide()}function getRow(t){getSumChannels();var e='<tr><td style=\"text-align: center;\">';return csvLink=\"/history/\"+t.substr(0,8)+\".csv\",deleteLink=\"/delete/\"+t.substr(0,8)+\".csv\",e+=(date=t.substr(0,4)+\"-\"+t.substr(4,2)+\"-\"+t.substr(6,2))+\"</td>\",e+='<td style=\"text-align: center;\">Raw Data: (<a href=\"'+csvLink+'\" target=\"_blank\" >CSV</a>)</td>',e+='<td><form method=\"post\" action='+deleteLink+'><button type=\"submit\">Delete</button></form></td></tr>'}function getCookie(t){for(var e=t+\"=\",n=document.cookie.split(\";\"),a=0;a<n.length;a++){for(var s=n[a];\" \"==s.charAt(0);)s=s.substring(1);if(-1!=s.indexOf(e))return s.substring(e.length,s.length)}return\"\"}function hideWarn(){$(\"#connection_warn\").hide()}var data0=[],data1=[],data2=[],data3=[],data4=[],plot0=[]</script><div id=\"loading\" style=\"text-align:center\"><h1 id=\"lH1\">Loading...</h1></div><div class=\"caution\" style=\"display:none\"><p>This station is marked as supplying live data, however the data appears to be old. Please check the age of the data carefully before using it!</p></div><div id=\"connection_warn\" style=\"text-align:center;width:800px;margin-right:auto;margin-left:auto;background-color:orange;color:#fff;display:none\" onclick=\"hideWarn()\"><h1>No Response From Server. Please check to make sure you are still connected to the internet</h1></div><h4 style=\"text-align:center\"><a href=\"table.html\" target=\"_blank\">Fault and Status Code Reference</a></h4><table style=\"margin-left:auto;margin-right:auto\" id=\"files\"></table><br><br><div style=\"text-align:center;padding-bottom:50px\"><h5 style=\"color:#666\">&copy; 2023. All rights reserved.<br><br><em>Powered by<a target=\"_blank\" href=\"https://www.solarstik.com/\">Solar Stik, Inc.</a></em></h5></div></body></html>";