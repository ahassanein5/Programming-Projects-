var Xval, Yval, elem;

var page = "";

function get(event) {
	
	elem = event.currentTarget;

	var Xpos = parseInt(elem.style.left);
	var Ypos = parseInt(elem.style.top);

	Xval = event.clientX - Xpos;
	Yval = event.clientY - Ypos;
 
	document.addEventListener("mousemove", move, true);
	document.addEventListener("mouseup", drop, true);

	event.stopPropagation();
	event.preventDefault();
	
}

function move(event) {
	
	elem.style.left = (event.clientX - Xval) + "px";
	elem.style.top = (event.clientY - Yval) + "px";

	event.stopPropagation();
	
}

function drop(event) {
	
	document.removeEventListener("mouseup", drop, true);
	document.removeEventListener("mousemove", move, true);

	event.stopPropagation();
	
}
			
function changeBackground() {	

	page += document.body.style.backgroundColor = document.getElementById('color').value;
	
}
			
function changeFontColor() {	
			
	page += document.body.style.color = document.getElementById('color1').value;	
	
}
			
function changeFontSize() {
	
	page += document.body.style.fontSize = document.getElementById('size').value;
	
}
			
function changeTextAlign() {
	
	page += document.body.style.textAlign = document.getElementById('place').value;

}
			
function addHeading() {
				
	var heading = prompt("Enter heading:");
	
	page += "<span style =  \"position: absolute; top: 1000px; left: 200px; \" onmousedown = \"get(event);\"> <h1>" + heading + "  </h1> </span>";
	document.cookie = "heading=" + heading;
	document.getElementById("userWebPage").innerHTML = page;
	
}
			
function addText() {
				
	var text = prompt("Enter text:");
	
	page += "<span style =  \"position: absolute; top: 950px; left: 150px; \" onmousedown = \"get(event);\"> <p>" + text + "  </p> </span>";
	document.cookie = "text=" + text;
	document.getElementById("userWebPage").innerHTML = page;				

}
			
function addDate() {
	
	var currentDate = new Date();

	page += "<span style =  \"position: absolute; top: 900px; left: 100px; \" onmousedown = \"get(event);\"> <span>" + currentDate.toLocaleString() + "  </span> </span>";
	document.cookie = "date=" + currentDate;
	document.getElementById("userWebPage").innerHTML = page;

}
			
function addLink() {
	
	var link = prompt("Enter link:");

	page += "<span style =  \"position: absolute; top: 1025px; left: 150px; \" onmousedown = \"get(event);\" > <a  href=" + "\"" + link + "\"" + ">Link</a> </span>";
	document.cookie = "link=" + link;
	document.getElementById("userWebPage").innerHTML = page;
				
}
			
function addLineBreak() {
	
	page += "<br />";
	document.getElementById("userWebPage").innerHTML = page;
				
}
			
function addHorizontalRule() {
				
	page += "<hr>";
	document.getElementById("userWebPage").innerHTML = page;
			
}
			
function addButton() {
				
	page += "<span style =  \"position: absolute; top: 950px; left: 250px; \" onmousedown = \"get(event);\"> <button>A do nothing button</button> </span>";
	document.cookie = "button=on";
	document.getElementById("userWebPage").innerHTML = page;
			
}

function addShortQuote() {
				
	var text = prompt("Enter quote:");
	
	page += "<span style =  \"position: absolute; top: 1000px; left: 100px; \" onmousedown = \"get(event);\"> <q>"+text+"</q> </span>";
	document.cookie = "short=" + text; 
	document.getElementById("userWebPage").innerHTML = page;

}

function addBlockquote() {
				
	var text = prompt("Enter your Block quote: ");
				
	page += "<span style =  \"position: absolute; top: 1100px; left: 100px; \" onmousedown = \"get(event);\"> <blockquote>"+text+"</blockquote> </span>";
	document.cookie = "block=" + text; 
	document.getElementById("userWebPage").innerHTML = page;
			
}

function addTextbox() {
	
	page += "<span style =  \"position: absolute; top: 1100px; left: 250px; \" onmousedown = \"get(event);\"> <textarea rows=4 cols=50></textarea> </span>";
	document.cookie = "box=on";
	document.getElementById("userWebPage").innerHTML = page;
			
}

function addImage() {
				
	var text = prompt("Please enter an image link: ");
				
	page += "<span style =  \"position: absolute; top: 1200px; left: 100px; \" onmousedown = \"get(event);\"> <img src="+text+" width=400px height= 300px> </span>";
	document.cookie = "image=" + text; 
	document.getElementById("userWebPage").innerHTML = page;
			
}

function addVideo() {
				
	var text = prompt("Please enter a video file: ");
	
	page += "<span style =  \"position: absolute; top: 1200px; left: 300px; \" onmousedown = \"get(event);\"> <video width=320 height=240 controls><source src="+text+" type=video/mp4></video> </span>";
	document.cookie = "video=" + text; 
	document.getElementById("userWebPage").innerHTML = page;
			
}

function setCookie() {

  var backColor = document.getElementById("color").value; 
  var fontCol = document.getElementById("color1").value;
  var fonts = document.getElementById("size").value; 
  var txtal = document.getElementById("place").value; 

    if(backColor != "")
      document.cookie = "backgroundColor=" + document.getElementById("color").value;
    if(fontCol != "")
      document.cookie = "color=" + document.getElementById("color1").value;
    if(fonts != "")
      document.cookie = "fontSize=" + document.getElementById("size").value;
    if(txtal != "")
      document.cookie = "textAlign=" + txtal;
}

function getCookie() {
	
  var cookiesArray = document.cookie.split("; ");

  for(var i = 0; i < cookiesArray.length; i++){

    var nameValueArray = cookiesArray[i].split("=");
    
    if (nameValueArray[0] == "backgroundColor")
    	  document.body.style.backgroundColor = nameValueArray[1];

    else if (nameValueArray[0] == "color")
     	 document.body.style.color = nameValueArray[1];

    else if (nameValueArray[0] == "fontSize")
     	 document.body.style.fontSize = nameValueArray[1];
	 
    else if (nameValueArray[0] == "textAlign")
      	 document.body.style.textAlign = nameValueArray[1];

    else if (nameValueArray[0] == "heading"){
    	if(nameValueArray[1] != "")
      		document.getElementById("userWebPage").innerHTML += "<span  style =  \"position: absolute; top: 1000px; left: 200px; \" onmousedown = \"get(event);\"> <h1>" + nameValueArray[1] + "  </h1> </span>";
    }
    else if (nameValueArray[0] == "text"){
    	if(nameValueArray[1] != "")
     	 	document.getElementById("userWebPage").innerHTML += "<span style =  \"position: absolute; top: 950px; left: 150px; \" onmousedown = \"get(event);\"> <p>" + nameValueArray[1] + "  </p> </span>";
    }
    else if (nameValueArray[0] == "date"){
    	if(nameValueArray[1] != "")
     		 document.getElementById("userWebPage").innerHTML += "<span style =  \"position: absolute; top: 900px; left: 100px; \" onmousedown = \"get(event);\"> <span>" + nameValueArray[1] + "  </span> </span>";
    }
    else if (nameValueArray[0] == "link"){
    	if(nameValueArray[1] != "")
      		document.getElementById("userWebPage").innerHTML += "<span style =  \"position: absolute; top: 1025px; left: 150px; \" onmousedown = \"get(event);\" > <a  href=" + "\"" + nameValueArray[i] + "\"" + ">Link</a> </span>";
    }
    else if (nameValueArray[0] == "button"){
    	if(nameValueArray[1] != "")
     	 	document.getElementById("userWebPage").innerHTML +=  "<span style =  \"position: absolute; top: 950px; left: 250px; \" onmousedown = \"get(event);\"> <button>A do nothing button</button> </span>";
    }
    else if (nameValueArray[0] == "short"){
    	if(nameValueArray[1] != "")
     	 	document.getElementById("userWebPage").innerHTML += "<span style =  \"position: absolute; top: 1000px; left: 100px; \" onmousedown = \"get(event);\"> <q>"+ nameValueArray[1] +"</q> </span>";
    }
    else if (nameValueArray[0] == "block"){
    	if(nameValueArray[1] != "")
			document.getElementById("userWebPage").innerHTML += "<span style =  \"position: absolute; top: 1100px; left: 100px; \" onmousedown = \"get(event);\"> <blockquote>"+ nameValueArray[1] +"</blockquote> </span>";
    }
    else if (nameValueArray[0] == "box"){
    	if(nameValueArray[1] != "")
     		 document.getElementById("userWebPage").innerHTML += "<span style =  \"position: absolute; top: 1100px; left: 250px; \" onmousedown = \"get(event);\"> <textarea rows=4 cols=50></textarea> </span>";
    }
    else if (nameValueArray[0] == "image"){
    	if(nameValueArray[1] != "")
     	 	document.getElementById("userWebPage").innerHTML += "<span style =  \"position: absolute; top: 1200px; left: 100px; \" onmousedown = \"get(event);\"> <img src="+ nameValueArray[1] +" width=400px height= 300px> </span>";
    }
    else if (nameValueArray[0] == "video"){
    	if(nameValueArray[1] != "")
    	  	document.getElementById("userWebPage").innerHTML += "<span style =  \"position: absolute; top: 1200px; left: 300px; \" onmousedown = \"get(event);\"> <video width=320 height=240 controls><source src="+ nameValueArray[1] +" type=video/mp4></video> </span>";
    }
  }
  
}

function removeCookies() {
	
    var res = document.cookie;
    var multiple = res.split(";");
	
    for(var i = 0; i < multiple.length; i++) {
        var key = multiple[i].split("=");
        document.cookie = key[0]+"=";
    }
	
}