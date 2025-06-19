import express from "express"
import cors from "cors"
import { connectDB } from "./config/db.js"
import foodRouter from "./routes/foodRoute.js"
import userRouter from "./routes/userRoute.js"
import 'dotenv/config'
import cartRouter from "./routes/cartRoute.js"
import orderRouter from "./routes/orderRoute.js"
import restaurantRouter from "./routes/restaurantRoute.js"

// App config
const app = express()
const port = process.env.PORT || 4000

// Middleware
app.use(cors()) // ✅ Enable CORS
app.use(express.json()) // ✅ Parse JSON bodies

// DB Connection
connectDB()

// API Endpoints
app.use("/api/food", foodRouter)
app.use("/api/user", userRouter)
app.use("/api/cart", cartRouter)
app.use("/api/order", orderRouter)
app.use("/api/restaurant", restaurantRouter)

// Serve uploaded images
app.use("/images", express.static("uploads"))

// Test endpoint
app.get("/", (req, res) => {
    res.send("API Working")
})

// Start server
app.listen(port, () => {
    console.log(`Server started on http://localhost:${port}`)
})
