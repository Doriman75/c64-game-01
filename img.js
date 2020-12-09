const fs = require("fs");

let data = fs.readFileSync("image.bin","utf-8").split("\n");
let bitmap_data = data[1]
					.split(",")
					.map(e=>parseInt(e.substring(1),16))
					

let screen_ram_data = data[4]
					.split(",")
					.map(e=>parseInt(e.substring(1),16))


let screen_color_data = data[7]
					.split(",")
					.map(e=>parseInt(e.substring(1),16))

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
	return result;
}

function decompress(compressed)
{
	let result = [];
	for(let i = 0; i < compressed.length; i+=2)
	{
		for(let j = 0;j < compressed[i+1];j++) result.push(compressed[i]);
	}
	
	return result;
}


let bd = compress(bitmap_data);
let srd = compress(screen_ram_data);
let scd = compress(screen_color_data);

console.log("#define BITMAP_DATA_LENGTH ", bd.length);
console.log("#define SCREEN_RAM_DATA_LENGTH ", srd.length);
console.log("#define SCREEN_COLOR_DATA_LENGTH ", scd.length);
console.log("char bitmap_data[] = {" +bd.map(e=>"0x" + ("00" + e.toString(16)).slice(-2)) + "};");
console.log("char screen_ram_data[] = {" +srd.map(e=>"0x" + ("00" + e.toString(16)).slice(-2)) + "};");
console.log("char screen_color_data[] = {" +scd.map(e=>"0x" + ("00" + e.toString(16)).slice(-2)) + "};");

let s = decompress(srd)

for(let i = 0; i < s.length; i++)
{
	if(s[i] != screen_ram_data[i]) console.log(s[i],screen_ram_data[i]); 
}