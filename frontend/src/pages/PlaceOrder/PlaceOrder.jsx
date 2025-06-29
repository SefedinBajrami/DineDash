import React, { useContext, useEffect, useState } from 'react'
import './PlaceOrder.css'
import { StoreContext } from '../../context/StoreContext'
import axios from "axios"
import { useNavigate } from 'react-router-dom'
import { toast } from 'react-toastify'

const PlaceOrder = () => {

  const { getTotalCartAmount, isDiscountApplied, token, food_list, cartItems, url } = useContext(StoreContext);

  const totalAmount = getTotalCartAmount() === 0 ? 0 :
    isDiscountApplied ? Math.round(getTotalCartAmount() * 0.9 + 20) : getTotalCartAmount() + 20;

  const [data, setData] = useState({
    firstName: "",
    lastName: "",
    email: "",
    street: "",
    city: "",
    state: "",
    zipcode: "",
    country: "",
    phone: ""
  })

  const onChangeHandler = (event) => {
    const name = event.target.name;
    const value = event.target.value;
    setData(data => ({ ...data, [name]: value }))
  }


  const placeOrder = async (event) => {
    event.preventDefault();
    let orderItems = [];
    food_list.map((item) => {
      if (cartItems[item._id] > 0) {
        let itemInfo = item;
        itemInfo["quantity"] = cartItems[item._id];
        orderItems.push(itemInfo)
      }
    })
    let orderData = {
      address: data,
      items: orderItems,
      amount: isDiscountApplied
        ? Math.round(getTotalCartAmount() * 0.9 + 20)
        : getTotalCartAmount() + 20,
      isDiscountApplied: isDiscountApplied,
    }
    let response = await axios.post(url + "/api/order/place", orderData, { headers: { token } });
    if (response.data.success) {
      const { session_url } = response.data;
      window.location.replace(session_url);
    }
    else {
      alert("Error");
    }
  }



  const navigate = useNavigate();
  useEffect(() => {
    if (!token) {
      navigate('/cart');
      toast.success("You need an account!")
    }
    else if (getTotalCartAmount() === 0) {
      navigate('/cart')
      toast.success("You have no items in your cart!")
    }
  }, [token])





  return (
    <form onSubmit={placeOrder} className='place-order'>
      <div className="place-order-left">
        <p className='title'>Delivery Information</p>
        <div className="multi-fields">
          <input name='firstName' onChange={onChangeHandler} value={data.firstName} type="text" placeholder='First Name' required />
          <input name='lastName' onChange={onChangeHandler} value={data.lastName} type="text" placeholder='Last Name' required />
        </div>
        <input name='email' onChange={onChangeHandler} value={data.email} type="email" placeholder='E-mail address' required />
        <input name='street' onChange={onChangeHandler} value={data.street} type="text" placeholder='Street' required />
        <div className="multi-fields">
          <input name='city' onChange={onChangeHandler} value={data.city} type="text" placeholder='City' required />
          <input name='state' onChange={onChangeHandler} value={data.state} type="text" placeholder='State' required />
        </div>
        <div className="multi-fields">
          <input name='zipcode' onChange={onChangeHandler} value={data.zipcode} type="text" placeholder='Zip code' required />
          <input name='country' onChange={onChangeHandler} value={data.country} type="text" placeholder='Country' required />
        </div>
        <input name='phone' onChange={onChangeHandler} value={data.phone} type="text" placeholder='Phone' required />
      </div>

      <div className="place-order-right">
        <div className="cart-total">
          <h2>Cart Total</h2>
          <div>
            <div className="cart-total-details">
              <p>Subtotal</p>
              <p>{getTotalCartAmount()} mkd </p>
            </div>
            <hr />
            <div className="cart-total-details">
              <p>Delivery Fee</p>
              <p>{getTotalCartAmount() === 0 ? 0 : 20} mkd </p>
            </div>
            <hr />
            <div className="cart-total-details">
              <b>Total</b>
              <b>{totalAmount} mkd</b>
            </div>

          </div>
          <button type='submit'>Proceed to payment</button>
        </div>
      </div>
    </form>
  )
}

export default PlaceOrder
