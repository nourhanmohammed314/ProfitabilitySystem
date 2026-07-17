from flask import Flask,request,jsonify,render_template
import subprocess
import json
app=Flask(__name__)
@app.template_filter("money")
def money(value):
    return f"{value:,.2f}"
@app.route("/")
def home():
    return render_template("index.html")

@app.route("/analyze",methods=["GET","POST"])
def analyze():
    if request.method=="POST":
        productId=request.form["productId"]
        startMonth=request.form["startMonth"]
        startYear=request.form["startYear"]
        endMonth=request.form["endMonth"]
        endYear=request.form["endYear"]
        result=subprocess.run(
            [
                "cpp/ProfitabilitySystem.exe",
                productId,
                startMonth,
                startYear,
                endMonth,
                endYear
            ],
            capture_output=True,
            text=True
        )
        data=json.loads(result.stdout)
        if "error" in data:
            return render_template("analyze.html", error=data["error"])
        return render_template("result.html",result=data)
    return render_template("analyze.html")

@app.route("/products")
def products():
    result=subprocess.run(
        [
            "cpp/ProfitabilitySystem.exe",
            "products"
        ],
        capture_output=True,
        text=True
    )
    data=json.loads(result.stdout)
    if "error" in data:
        return render_template("products.html", error=data["error"])
    return render_template("products.html",products=data)
if __name__=="__main__":
    app.run(debug=True)