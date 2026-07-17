const form = document.querySelector("form");
const startMonth = document.getElementById("SMonth");
const startYear = document.getElementById("SYear");
const endMonth = document.getElementById("EMonth");
const endYear = document.getElementById("EYear");
const error = document.getElementById("jsError");
const button = document.querySelector("button[type='submit']");
form.addEventListener("submit", function (event) {
    const start = Number(startYear.value) * 12 + Number(startMonth.value);
    const end = Number(endYear.value) * 12 + Number(endMonth.value);
    if (start > end)
    {
        event.preventDefault();
        error.textContent = "Start date must be before or equal to end date.";
        error.style.display = "block";
    }
    else
    {
    error.style.display = "none";
    button.disabled = true;
    button.textContent = "Analyzing...";
    }
});
