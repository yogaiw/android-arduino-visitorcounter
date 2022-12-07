package com.hureyo.viscount

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.LinearLayoutManager
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import com.hureyo.viscount.adapters.SuhuAdapter
import com.hureyo.viscount.model.Suhu
import kotlinx.android.synthetic.main.activity_suhu.*
import kotlinx.android.synthetic.main.item_suhu.*

class SuhuActivity : AppCompatActivity() {

    private val suhuRef = FirebaseDatabase.getInstance().reference.child("Suhu")
    private val list = ArrayList<Suhu>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_suhu)

        rv_suhu.setHasFixedSize(true)
        rv_suhu.layoutManager = LinearLayoutManager(this)

        suhuRef.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(p0: DataSnapshot) {
                list.clear()
                for (suhuSnapshot in p0.children) {
                    val suhu = suhuSnapshot.getValue(Suhu::class.java)
                    list.add(suhu!!)
                }
                val adapter = SuhuAdapter(list)
                rv_suhu.adapter = adapter
            }

            override fun onCancelled(p0: DatabaseError) {
                TODO("Not yet implemented")
            }

        })

        btn_resetSuhu.setOnClickListener {
            resetSuhu()
        }
    }

    private fun resetSuhu() {
        val suhu = Suhu(0.0)
        suhuRef.removeValue()
        suhuRef.child("1").setValue(suhu)
    }
}