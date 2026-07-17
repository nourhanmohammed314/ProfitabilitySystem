const search=document.getElementById("search")
const rows=document.querySelectorAll("#productsTable tr")
const noResult = document.getElementById("noResult");
const tableContainer = document.getElementById("tableContainer");
search.addEventListener("input",function(){
const text=search.value.toLowerCase();
let found = false;
rows.forEach(function(row){
    const productName=row.cells[1].textContent.toLowerCase();
    if (productName.includes(text)) 
    {
    row.style.display = "";
    found = true;
    } 
    else
    {
    row.style.display = "none";
    }
});
if (found) {
    noResult.style.display = "none";
    tableContainer.style.display = "block";
} else {
    noResult.style.display = "block";
    tableContainer.style.display = "none";
}
});