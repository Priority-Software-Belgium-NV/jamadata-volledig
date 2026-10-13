// Processing HelloRequest and sending HelloResponse
        
		/// <summary>
        /// Handle an incoming "hello request" message.
        /// </summary>
        /// <param name="requestMessage">The hello request message.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleHelloRequest(TlvLib.TlvMessageEcr requestMessage)
        {
            // Store the terminal ID.
            TlvLib.Tlv tlvTerminalId = requestMessage.Header.FindTlv((uint)TlvLib.Tag.TerminalId);
            if (tlvTerminalId != null) mTerminalId = tlvTerminalId.GetValueFromString();

            // Process the connection parameters (keep-alive).
            TlvLib.TlvConstructed tlvConnectionParameters = requestMessage.Body.FindTlvConstructed((uint)TlvLib.Tag.Group_ConnectionParameters);
            if (tlvConnectionParameters != null)
            {
                TlvLib.Tlv tlvKeepAliveInterval = tlvConnectionParameters.FindTlv((uint)TlvLib.Tag.KeepAliveInterval);
                if (tlvKeepAliveInterval != null) mKeepAliveInterval = tlvKeepAliveInterval.GetValueUInt16FromBcd();
            }

            DisplayMessage(String.Format("Hello request received from: {0}, Requested keep-alive interval: {1}", mTerminalId, mKeepAliveInterval));

            // Create response message.
            TlvLib.TlvMessageEcr responseMessage = CreateMessage(TlvLib.MessageType.HelloResponse);

            // Fill the body.

            // Set result code.
            responseMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.ResultCode, (ushort)TlvLib.EcrResultCode.ResultOK);

           	// Add connection parameters with keep-alive interval.
	        {
		        TlvLib.TlvConstructed connectionParameters = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_ConnectionParameters);
		        connectionParameters.AddTlvUInt16AsBcd((uint)TlvLib.Tag.KeepAliveInterval, 0);  // Normally the value received in the request is sent back and used. Here we tell the terminal not to use keep-alives.
                responseMessage.Body.AddTlv(connectionParameters);
	        }

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(responseMessage);
            }
            catch (Exception ex)
            {
                DisplayMessage(String.Format("Error sending hello response: {0)", ex.Message), true, Color.White, Color.Red);
            }

            return true;
        }
		
		
// Sending TransactionRequest.


        /// <summary>
        /// Start a transaction (can be called from non GUI threads).
        /// </summary>
        private void StartTransaction()
        {

			DisplayMessage("Transaction started.");

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TransactionRequest);


			// Create transaction data.
			TlvLib.TlvConstructed tlvTransactionData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_TransactionData);
			tlvTransactionData.AddTlvUInt32AsBcd((uint)TlvLib.Tag.Amount, mAmount);
			tlvTransactionData.AddTlvUInt16AsBcd((uint)TlvLib.Tag.CurrencyCode, 978);   // Euro.
			tlvTransactionData.AddTlvUInt8AsBcd((uint)TlvLib.Tag.CurrencyExponent, 2);  // Cents.
			tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.TransactionReference, txtReference.Text);
			tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.TransactionType, (byte)(TlvLib.TransactionType)cbTransactionType.SelectedItem);
			requestMessage.Body.AddTlv(tlvTransactionData);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.Ecr);
			requestMessage.Body.AddTlv(tlvPrintData);               

			// Set transaction ID.
			requestMessage.Body.AddTlvUInt64AsHex((uint)TlvLib.Tag.TransactionId, mTransactionId++);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
			}
			catch (Exception ex)
			{
				DisplayMessage(String.Format("Error sending bye request: {0)", ex.Message), true, Color.White, Color.Red);
			}

		}
		
		
// Handling transaction response.

        /// <summary>
        /// Handle an incoming "transaction response" message.
        /// </summary>
        /// <param name="transactionResponse">The transaction response body.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleTransactionResponse(TlvLib.TlvConstructed transactionResponse)
        {
            string cardholderTicket = "";
            string merchantTicket = "";
            string journalTicket = "";

            // Extract ticket data.
            TlvLib.TlvConstructed tlvTicketData = transactionResponse.FindTlvConstructed((uint)TlvLib.Tag.Group_TicketData);
            foreach (TlvLib.TlvConstructed tlvTicket in tlvTicketData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
            {
                switch ((TlvLib.TicketType)tlvTicket.FindTlv((uint)TlvLib.Tag.TicketType).GetValueUInt8FromHex())
                {
                    case TlvLib.TicketType.CardHolder:
                        cardholderTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                        break;

                    case TlvLib.TicketType.Merchant:
                        merchantTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                        break;

                    case TlvLib.TicketType.Journal:
                        journalTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                        break;
                }
            }

            // Display the tickets.
            DisplayTickets(cardholderTicket, merchantTicket, journalTicket);

            // Display result.
            TlvLib.TransactionResult transactionResult = (TlvLib.TransactionResult)transactionResponse.FindTlv((uint)TlvLib.Tag.TransactionResult).GetValueUInt8FromHex();
            TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)transactionResponse.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt8FromHex();
            DisplayMessage(String.Format("Transaction result received: {0} [Result code: {1}]", transactionResult, resultCode));

            return true;
        }


// Sending bye request.

        /// <summary>
        /// Send a bye request message.
        /// </summary>
        /// <param name="reason">The bye reason to send.</param>
        private void SendByeRequest(TlvLib.ByeReason reason)
        {
            // Create request message.
            TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.ByeRequest);

            // Fill the reason.
            requestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.ByeReason, (byte)reason);

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(requestMessage);
            }
            catch (Exception ex)
            {
                DisplayMessage(String.Format("Error sending bye request: {0)", ex.Message), true, Color.White, Color.Red);
            }
        }

		
// Handling bye response.

        /// <summary>
        /// Handle an incoming "bye response" message.
        /// </summary>
        /// <param name="byeResponse">The bye response body.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleByeResponse(TlvLib.TlvConstructed byeResponse)
        {
            DisplayMessage("Terminal disconnected.");
            return false;
        }
