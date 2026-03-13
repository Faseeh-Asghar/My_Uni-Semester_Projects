document.addEventListener('DOMContentLoaded', () => {
  // Signup Form handling
  const signupForm = document.getElementById('signup-container');
  if (signupForm) {
    signupForm.addEventListener('submit', (event) => {
      event.preventDefault();
      alert('You have signed up successfully!');
      
      // Redirect to menu page
      window.location.href = 'menu.html'; 
    });
  }

  
  const loginForm = document.getElementById('login-container');
  if (loginForm) {
    loginForm.addEventListener('submit', (event) => {
      event.preventDefault();
      alert('You have logged in successfully!');
      
      // Redirect to menu page
      window.location.href = 'menu.html'; 
    });
  }

  


  // Cart handling
  const cartItemsContainer = document.querySelector('.cart-items');
  const totalPriceElement = document.querySelector('.total-price');
  const cartKey = 'cart'; // Local storage key for the cart
  const checkoutButton = document.querySelector('.checkout-btn'); // Checkout button

  // Ensure cart elements are available
  if (cartItemsContainer && totalPriceElement && checkoutButton) {
   
    function getCart() {
      return JSON.parse(localStorage.getItem(cartKey)) || [];
    }

    
    function saveCart(cart) {
      localStorage.setItem(cartKey, JSON.stringify(cart));
    }

    // Function to display cart items
    function displayCartItems() {
      const cartItems = getCart();
      cartItemsContainer.innerHTML = ''; // Clear current cart items

      if (cartItems.length === 0) {
        cartItemsContainer.innerHTML = '<p>Your cart is empty.</p>';
        totalPriceElement.textContent = '$0.00'; // Reset total price
      } else {
        cartItems.forEach(item => {
          const cartItemElement = document.createElement('div');
          cartItemElement.classList.add('cart-item');

          cartItemElement.innerHTML = `
            <img src="${item.image}" alt="${item.name}" class="item-image">
            <div class="item-details">
              <p class="item-name">${item.name}</p>
              <p class="item-price">$${item.price.toFixed(2)}</p>
              <input type="number" class="item-quantity" value="${item.quantity}" min="1">
            </div>
            <button class="remove-btn">Remove</button>
          `;

          // Append item to the cart
          cartItemsContainer.appendChild(cartItemElement);
        });

        // Calculate the total price
        calculateTotal();
      }
    }

    // Function to calculate the total price
    function calculateTotal() {
      const cartItems = getCart();
      let total = 0;
      cartItems.forEach(item => {
        total += item.price * item.quantity;
      });

      totalPriceElement.textContent = `$${total.toFixed(2)}`;
    }

    // Handle quantity change
    cartItemsContainer.addEventListener('input', (event) => {
      if (event.target.classList.contains('item-quantity')) {
        const quantity = parseInt(event.target.value);
        const cartItemElement = event.target.closest('.cart-item');
        const itemName = cartItemElement.querySelector('.item-name').textContent;
        const cart = getCart();
        const itemIndex = cart.findIndex(item => item.name === itemName);

        if (quantity > 0) {
          // Update the cart item quantity
          cart[itemIndex].quantity = quantity;
          saveCart(cart);
          calculateTotal();
        } else {
          alert('Quantity must be at least 1');
          event.target.value = 1;
        }
      }
    });

    // Handle remove button click
    cartItemsContainer.addEventListener('click', (event) => {
      if (event.target.classList.contains('remove-btn')) {
        const cartItemElement = event.target.closest('.cart-item');
        const itemName = cartItemElement.querySelector('.item-name').textContent;
        let cart = getCart();

        // Remove the item from the cart
        cart = cart.filter(item => item.name !== itemName);
        saveCart(cart);
        displayCartItems();
      }
    });

    // Checkout button click handler
    checkoutButton.addEventListener('click', () => {
      const cartItems = getCart();
      if (cartItems.length === 0) {
        alert('Your cart is empty! Please add items to the cart.');
      } else {
        // Show checkout alert
        alert('Thank you for your purchase! Your order has been placed.');

        // Clear the cart
        localStorage.removeItem(cartKey);
        displayCartItems(); // Update UI to reflect empty cart
      }
    });

    // Initialize cart display
    displayCartItems();
  }

  // Add to cart handling
  const orderButtons = document.querySelectorAll('.order-btn');
  if (orderButtons.length > 0) {
    // Function to get the current cart from localStorage
    function getCart() {
      const cart = JSON.parse(localStorage.getItem(cartKey)) || [];
      console.log('Cart retrieved:', cart); 
      return cart;
    }

    // Function to save the cart back to localStorage
    function saveCart(cart) {
      console.log('Saving cart:', cart); // Debugging: Check cart to be saved
      localStorage.setItem(cartKey, JSON.stringify(cart));
    }

    // Add item to the cart
    function addToCart(item) {
      console.log('Adding item to cart:', item);  // Debugging: Check item details
      const cart = getCart();
      console.log("Current Cart:", cart); // Debugging: Check current cart contents

      // Check if the item already exists in the cart
      const existingItemIndex = cart.findIndex(cartItem => cartItem.name === item.name);
      console.log("Existing item index:", existingItemIndex); // Debugging: Check if item exists

      if (existingItemIndex > -1) {
        // If the item exists, increase its quantity
        cart[existingItemIndex].quantity += 1;
        console.log(`${item.name} quantity updated. New Quantity: ${cart[existingItemIndex].quantity}`);
      } else {
        // If the item doesn't exist, add it to the cart
        cart.push(item);
        console.log(`${item.name} added to the cart.`);
      }

      // Save updated cart
      saveCart(cart);
      alert(`${item.name} has been added to your cart!`);

      // Debugging: Check the updated cart
      console.log("Updated Cart:", cart);

      // Optionally, update the UI here to reflect the new cart state.
      updateCartDisplay();
    }

    // Attach event listeners to all "Order Now" buttons
    orderButtons.forEach(button => {
      button.addEventListener('click', (event) => {
        // Get product details from the button's data-* attributes
        const name = event.target.getAttribute('data-name');
        const price = parseFloat(event.target.getAttribute('data-price'));
        const image = event.target.getAttribute('data-image');

        // Create item object
        const item = {
          name,
          price,
          image,
          quantity: 1 // Default quantity
        };

        addToCart(item);
      });
    });

    // Function to update the cart display (if you want to show the cart on the page)
    function updateCartDisplay() {
      const cart = getCart();
      const cartItemCount = cart.reduce((total, item) => total + item.quantity, 0);
      console.log('Updated cart item count:', cartItemCount);  // Debugging: Check item count
      const cartCountElement = document.querySelector('.cart-count'); // Adjust this selector if necessary
      if (cartCountElement) {
        cartCountElement.textContent = cartItemCount; // Update cart item count
      }
    }

    // Optionally, you can call updateCartDisplay on page load to show the current cart count
    updateCartDisplay();
  }
});

document.addEventListener('DOMContentLoaded', () => {
  const cartKey = 'cart'; // Local storage key for the cart
  const cart = JSON.parse(localStorage.getItem(cartKey)) || []; // Get existing cart or initialize empty one

  // Function to save the cart back to localStorage
  function saveCart() {
    localStorage.setItem(cartKey, JSON.stringify(cart));
  }

  // Function to display the cart items in the UI (optional, could be added to a cart page)
  function updateCartDisplay() {
    const cartCount = cart.reduce((total, item) => total + item.quantity, 0);
    const cartCountElement = document.querySelector('.cart-count');
    if (cartCountElement) {
      cartCountElement.textContent = cartCount;
    }
  }

  // Add event listeners to all "Order now" buttons
  document.querySelectorAll('button[data-name]').forEach(button => {
    button.addEventListener('click', (event) => {
      const itemName = event.target.getAttribute('data-name');
      const itemPrice = parseFloat(event.target.getAttribute('data-price'));
      const itemImage = event.target.getAttribute('data-image'); // Get the image from the data attribute

      // Check if item already exists in the cart
      const existingItemIndex = cart.findIndex(item => item.name === itemName);
      
      if (existingItemIndex > -1) {
        // If the item exists, increase its quantity
        cart[existingItemIndex].quantity += 1;
      } else {
        // If the item doesn't exist, add it to the cart with quantity 1
        cart.push({
          name: itemName,
          price: itemPrice,
          quantity: 1,
          image: itemImage // Save the image with the item
        });
      }

      saveCart();
      updateCartDisplay();
      alert(`${itemName} has been added to your cart!`);
    });
  });

  // Initialize cart display
  updateCartDisplay();
});
