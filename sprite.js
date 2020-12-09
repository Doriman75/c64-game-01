const fs = require("fs");

let sprite = fs.readFileSync(process.argv[2],"utf-8")
				.trim()
				.replace(/,/g, " ")
				.replace(/\t/g, " ")
				.replace(/\n/g, " ")
				.replace(/  /g, " ")
				.replace(/ /g, ",")
				.replace(/\$/g, "0x")
				
console.log("char ", process.argv[2].split("\\").pop().split(".")[0],"[] = {", sprite, "};")
