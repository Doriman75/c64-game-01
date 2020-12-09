const fs = require("fs");

function compress(data)
{
	let result = [];
	let current = data[0];
	for(let i = 0; i < data.length;)
	{
		result.push(current);
		let c = 0;
		while(data[i] == current && i < data.length && c < 255) { c++; i++;}
		result.push(c);
		current=data[i]
	}
	
	if(result.length < data.length && false)
	{
		result = [1].concat(result);
	}
	else
	{
		result = [0].concat(data);		
	}
	
	let l = result.length +3;
	result.unshift(l % 256)
	result.unshift(Math.floor(l / 256))
	return result;
}

let data = fs.readFileSync(process.argv[2],"utf-8")
				.trim()
				.replace(/,/g, " ")
				.replace(/\t/g, " ")
				.replace(/\n/g, " ")
				.replace(/\r/g, " ")
				.replace(/  /g, " ")
				.replace(/ /g, ",")
				.replace(/\$/g, "0x")
				.split(",")
				.filter(e=>e.trim().length > 0)

//console.log("char ", process.argv[2].split("\\").pop().split(".")[0].trim() + "[] = {", compress(data).join(","), "};")
console.log("char ", process.argv[2].split("\\").pop().split(".")[0].trim() + "[] = {", data.join(","), "};")


