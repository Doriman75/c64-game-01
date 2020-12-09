const fs = require("fs");

let sprite = fs.readFileSync("sprite0.txt","utf-8")
				.split("\n")
				.filter(e=>e.startsWith("!byte"))
				.map(e=>!e.startsWith("!byte")?e:e.substring(6))
				.map(e=>e.replace(/\$/g, "0x"))
				.map(e=>e.split(","))
				.reduce((r,e)=>r.concat(e),[])
				.join(",")
				
console.log("char ", process.argv[2].split("\\").pop().split(".")[0],"[] = {", sprite, "};")