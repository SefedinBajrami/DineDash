import mongoose from "mongoose";

export const connectDB = async () => {
    await mongoose.connect('mongodb+srv://sb30683:01d0vFlGBbEXSkGN@cluster0.i0lpabc.mongodb.net/DineDash').then(() => console.log("DB Connected"));
}