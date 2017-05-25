<?php

require_once(drupal_get_path('module', 'heydesk_peyment') . '/QuickPay/QuickPay.php');
require_once(drupal_get_path('module', 'heydesk_peyment') . '/QuickPay/API/Client.php');
dpm(drupal_get_path('module', 'heydesk_peyment') . '/QuickPay/QuickPay.php');

use QuickPay/QuickPay as Client;
  use Models/Order;
  //
  class PaymentController {
    public function pay(Request $request) {
      $order = new Order([
        'name' => $request('name'),
        'address' => $request('address'),
        'zipcode' => $request('zipcode'),
        'city' => $request('city')
      ]);

      $order->save();

      $client = new Client(":{$this->config('6bd35908e840ee17a048293e20ddab3efdae153767301fb4dce6fbc40dd78e8a')}");

      $token = $request('card_token');

      $payment = $client->request->post("/payments", [
        'order_id' => $order->order_id, // Must be unique
        'currency' => 'EUR'
      ])->as_object();

      $order->payment_id = $payment->id;
      $order->save();

      $payment = $client->request->post("/payments/{$order->payment_id}/authorize?synchronized", [
        'amount' => 12345,
        'card' => ['token' => $token]
      ]);

      if ($payment->accepted) {
        $order->authorized = TRUE;
      }

      $authorize = end($payment->operations);

      $order->qp_status_code = $authorize->qp_status_code;
      $order->qp_status_msg = $authorize->qp_status_msg;
      $order->aq_status_code = $authorize->aq_status_code;
      $order->aq_status_msg = $authorize->aq_status_msg;
      $order->save();

      if ($order->authorized()) {
        $this->session('order_id', $order->id);
        $this->redirectTo('/payment/receipt');
      }
      else {
        $this->render('error');
      }
    }

    public function receipt() {
      $order = Order::find($this->session('order_id'));
      $this->render('receipt', compact('order'));
    }
  }