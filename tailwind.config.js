/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./src/**/*.{html,js}"],
  theme: {
    extend: {
      colors: {
        primary: {
          50: '#effefc',
          100: '#c8fff9',
          200: '#90fff4',
          300: '#51f7ed',
          400: '#1de4df',
          500: '#05c7c5',
          600: '#00a0a1',
          700: '#057e80',
          800: '#0a6265',
          900: '#0e5053',
          950: '#003135',
        },
        secondary: {
          50: '#fbf6f1',
          100: '#f6eade',
          200: '#ebd2bd',
          300: '#deb293',
          400: '#d08c67',
          500: '#c67049',
          600: '#b85c3e',
          700: '#964734',
          800: '#7b3c31',
          900: '#64332a',
          950: '#351915',
        },
      },
    },
  },
  plugins: [],
}